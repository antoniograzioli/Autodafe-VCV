#!/usr/bin/env python3
"""Run with python3 scripts/test-tool-selection.py; no downloads or builds."""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


SCRIPT = Path(__file__).resolve().with_name("build-dependencies.sh")
WINDOWS_PREFIX = "x86_64-w64-mingw32-"
CMAKE_REACHED = 99


class ToolSelectionTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="tool-selection-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        scripts = self.root / "scripts"
        scripts.mkdir()
        self.script = scripts / SCRIPT.name
        shutil.copyfile(SCRIPT, self.script)
        self.bin = self.root / "bin"
        self.bin.mkdir()

        # Isolate PATH so installed host/cross tools cannot affect the tests.
        for utility in ("dirname", "mkdir", "cat", "grep"):
            resolved = shutil.which(utility)
            self.assertIsNotNone(resolved, utility)
            (self.bin / utility).symlink_to(resolved)
        self.make_tool("shasum", "exit 0\n")
        # Stop the real script after selection/validation, before any build.
        self.make_tool("cmake", f'printf "CMAKE: %s\\n" "$@"\nexit {CMAKE_REACHED}\n')
        for tool in ("cc", "c++", "g++", "ar", "ranlib", WINDOWS_PREFIX + "gcc", WINDOWS_PREFIX + "g++"):
            self.make_tool(tool)
        # Deliberately omit prefixed ar/ranlib: merely finding prefixed GCC
        # must not replace the tools supplied by a native Rack/MSYS2 build.

        self.environment = {
            "PATH": str(self.bin),
            "CC": "cc",
            "CXX": "c++",
            "AR": "ar",
            "RANLIB": "",
            "CROSS_COMPILE": "",
            "MACHINE": "",
            "MOCK_COMPILER_TARGET": "x86_64-w64-mingw32",
        }

    def make_tool(self, name, body=None):
        if body is None:
            body = 'if [ "${1:-}" = -dumpmachine ]; then printf "%s\\n" "$MOCK_COMPILER_TARGET"; fi\n'
        tool = self.bin / name
        tool.write_text("#!/bin/sh\n" + body)
        tool.chmod(0o755)

    def run_selection(self, arch, **overrides):
        # Seed placeholder cached sources. Only checksum verification is
        # stubbed; the production script still selects and validates tools.
        dependencies = self.root / "build" / "deps" / arch
        downloads = dependencies / "downloads"
        downloads.mkdir(parents=True, exist_ok=True)
        script = self.script.read_text()
        for variable, name in (("STK_COMMIT", "stk"), ("GAMMA_COMMIT", "Gamma")):
            commit = re.search(rf"^{variable}=(\w+)$", script, re.MULTILINE).group(1)
            (downloads / f"{name}-{commit}.tar.gz").touch()
            source = dependencies / "src" / name
            source.mkdir(parents=True, exist_ok=True)
            (source / ".source-commit").write_text(commit + "\n")
            (source / "CMakeLists.txt").write_text("set(STK_SRC)\n")
        return subprocess.run(
            ["/bin/sh", str(self.script), arch, str(dependencies / "prefix")],
            env={**self.environment, **overrides},
            capture_output=True,
            text=True,
            timeout=10,
        )

    def assert_selected(self, result, cc, cxx, ar, ranlib):
        self.assertEqual(result.returncode, CMAKE_REACHED, result.stdout + result.stderr)
        for label, tool in (("CC", cc), ("CXX", cxx), ("AR", ar), ("RANLIB", ranlib)):
            self.assertIn(f"{label}: {tool}", result.stdout.splitlines())
        for flag, tool in (("C_COMPILER", cc), ("CXX_COMPILER", cxx)):
            self.assertIn(f"CMAKE: -DCMAKE_{flag}={tool}", result.stdout.splitlines())
        for flag, tool in (("AR", ar), ("RANLIB", ranlib)):
            resolved = shutil.which(tool, path=str(self.bin))
            self.assertIn(f"CMAKE: -DCMAKE_{flag}={resolved}", result.stdout.splitlines())

    def test_native_windows_ignores_machine_prefix(self):
        result = self.run_selection("win-x64", CXX="g++", MACHINE="x86_64-w64-mingw32")
        self.assert_selected(result, "cc", "g++", "ar", "ranlib")

    def test_windows_cross_compile_uses_explicit_prefix(self):
        for suffix in ("gcc", "g++", "ar", "ranlib"):
            self.make_tool(WINDOWS_PREFIX + suffix)
        result = self.run_selection(
            "win-x64", CROSS_COMPILE=WINDOWS_PREFIX, MACHINE=WINDOWS_PREFIX,
            CC="unused-cc", CXX="unused-cxx", AR="unused-ar", RANLIB="unused-ranlib",
        )
        self.assert_selected(result, *(WINDOWS_PREFIX + suffix for suffix in ("gcc", "g++", "ar", "ranlib")))

    def test_native_macos_preserves_rack_compilers(self):
        for arch in ("mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                result = self.run_selection(arch, MACHINE="arm64-apple-darwin25.6.0")
                self.assert_selected(result, "cc", "c++", "ar", "ranlib")

    def test_native_builds_preserve_supplied_tools(self):
        supplied = dict(CC="custom-cc", CXX="custom-cxx", AR="custom-ar", RANLIB="custom-ranlib")
        for tool in supplied.values():
            self.make_tool(tool)
        for arch in ("win-x64", "mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                result = self.run_selection(arch, MACHINE="x86_64-w64-mingw32", **supplied)
                self.assert_selected(result, *supplied.values())

    def test_native_builds_default_empty_tools(self):
        for arch in ("win-x64", "mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                result = self.run_selection(arch, CC="", CXX="", AR="", RANLIB="")
                self.assert_selected(result, "cc", "c++", "ar", "ranlib")

    def test_native_builds_validate_every_tool(self):
        for arch in ("win-x64", "mac-arm64", "mac-x64"):
            for variable in ("CC", "CXX", "AR", "RANLIB"):
                with self.subTest(arch=arch, tool=variable):
                    result = self.run_selection(arch, **{variable: "missing-tool"})
                    self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                    self.assertIn("Required tool missing-tool not found in PATH", result.stderr)

    def test_windows_cross_compile_validates_every_prefixed_tool(self):
        for suffix in ("gcc", "g++", "ar", "ranlib"):
            self.make_tool(WINDOWS_PREFIX + suffix)
        for suffix in ("gcc", "g++", "ar", "ranlib"):
            with self.subTest(tool=suffix):
                tool = WINDOWS_PREFIX + suffix
                (self.bin / tool).unlink()
                result = self.run_selection("win-x64", CROSS_COMPILE=WINDOWS_PREFIX)
                self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                self.assertIn(f"Required tool {tool} not found in PATH", result.stderr)
                self.make_tool(tool)

    def test_windows_rejects_non_windows_compiler(self):
        result = self.run_selection(
            "win-x64", MACHINE="x86_64-w64-mingw32", MOCK_COMPILER_TARGET="arm64-apple-darwin25.6.0",
        )
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("Compiler cc does not target Windows", result.stderr)

    def test_linux_tool_selection_is_unchanged(self):
        ar = "x86_64-ubuntu16.04-linux-gnu-ar"
        ranlib = "x86_64-ubuntu16.04-linux-gnu-ranlib"
        self.make_tool(ar)
        self.make_tool(ranlib)
        result = self.run_selection("lin-x64")
        self.assert_selected(result, "cc", "c++", str(self.bin / ar), str(self.bin / ranlib))


if __name__ == "__main__":
    unittest.main(verbosity=2)
