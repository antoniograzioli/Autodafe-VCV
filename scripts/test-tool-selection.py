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
        self.script.chmod(0o755)
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

    def test_official_windows_compiler_selects_archive_tools_without_cross_compile(self):
        for suffix in ("ar", "ranlib"):
            self.make_tool(WINDOWS_PREFIX + suffix)
        for supplied_ar, supplied_ranlib in (("", ""), ("custom-ar", "custom-ranlib"),
                                             ("ar", "ranlib"), ("custom-ar", "")):
            with self.subTest(ar=supplied_ar, ranlib=supplied_ranlib):
                for tool in (supplied_ar, supplied_ranlib):
                    if tool:
                        self.make_tool(tool)
                result = self.run_selection(
                    "win-x64", CC=WINDOWS_PREFIX + "gcc", CXX=WINDOWS_PREFIX + "g++",
                    AR=supplied_ar, RANLIB=supplied_ranlib, MACHINE=WINDOWS_PREFIX[:-1],
                )
                self.assert_selected(result, WINDOWS_PREFIX + "gcc", WINDOWS_PREFIX + "g++",
                                     supplied_ar or WINDOWS_PREFIX + "ar",
                                     supplied_ranlib or WINDOWS_PREFIX + "ranlib")

    def test_native_windows_ignores_machine_even_when_prefixed_tools_exist(self):
        for suffix in ("ar", "ranlib"):
            self.make_tool(WINDOWS_PREFIX + suffix)
        result = self.run_selection("win-x64", MACHINE=WINDOWS_PREFIX[:-1])
        self.assert_selected(result, "cc", "c++", "ar", "ranlib")

    def test_native_macos_preserves_rack_compilers(self):
        for arch in ("mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                result = self.run_selection(arch, MACHINE="arm64-apple-darwin25.6.0")
                self.assert_selected(result, "cc", "c++", "ar", "ranlib")

    def test_native_macos_clang_uses_default_archive_tools(self):
        self.make_tool("clang")
        for arch in ("mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                result = self.run_selection(arch, CC="clang")
                self.assert_selected(result, "clang", "c++", "ar", "ranlib")

    def osxcross_tools(self, arch):
        cpu = "arm64" if arch == "mac-arm64" else "x86_64"
        prefix = f"{cpu}-apple-darwin21.4-"
        tools = [prefix + suffix for suffix in ("clang", "clang++-libc++", "ar", "ranlib")]
        for tool in tools:
            self.make_tool(tool)
        return tools

    def test_osxcross_selects_archive_tools(self):
        for arch in ("mac-arm64", "mac-x64"):
            with self.subTest(arch=arch):
                cc, cxx, ar, ranlib = self.osxcross_tools(arch)
                result = self.run_selection(arch, CC=cc, CXX=cxx, AR="", RANLIB="")
                self.assert_selected(result, cc, cxx, ar, ranlib)

    def test_osxcross_defaults_unset_archive_tools(self):
        cc, cxx, ar, ranlib = self.osxcross_tools("mac-arm64")
        del self.environment["AR"]
        del self.environment["RANLIB"]
        result = self.run_selection("mac-arm64", CC=cc, CXX=cxx)
        self.assert_selected(result, cc, cxx, ar, ranlib)

    def test_osxcross_preserves_each_explicit_override(self):
        for arch in ("mac-arm64", "mac-x64"):
            cc, cxx, cross_ar, cross_ranlib = self.osxcross_tools(arch)
            for ar, ranlib in (("custom-ar", "custom-ranlib"), ("ar", "ranlib"),
                               ("custom-ar", ""), ("", "custom-ranlib")):
                with self.subTest(arch=arch, ar=ar, ranlib=ranlib):
                    for tool in (ar, ranlib):
                        if tool:
                            self.make_tool(tool)
                    result = self.run_selection(arch, CC=cc, CXX=cxx, AR=ar, RANLIB=ranlib)
                    self.assert_selected(result, cc, cxx, ar or cross_ar, ranlib or cross_ranlib)

    def test_osxcross_only_selects_available_tools(self):
        for missing in ("ar", "ranlib", "both"):
            with self.subTest(missing=missing):
                cc, cxx, ar, ranlib = self.osxcross_tools("mac-arm64")
                if missing in ("ar", "both"):
                    (self.bin / ar).unlink()
                if missing in ("ranlib", "both"):
                    (self.bin / ranlib).unlink()
                result = self.run_selection("mac-arm64", CC=cc, CXX=cxx, AR="", RANLIB="")
                self.assert_selected(result, cc, cxx,
                                     "ar" if missing in ("ar", "both") else ar,
                                     "ranlib" if missing in ("ranlib", "both") else ranlib)

    def test_make_cross_builds_distinguish_builtin_ar_from_overrides(self):
        # Use the real dependency recipe with a minimal Rack makefile framework.
        shutil.copyfile(SCRIPT.parent.parent / "Makefile", self.root / "Makefile")
        sdk = self.root / "sdk"
        sdk.mkdir()
        del self.environment["AR"]
        del self.environment["RANLIB"]
        for arch in ("mac-arm64", "win-x64"):
            if arch == "mac-arm64":
                cc, cxx, ar, ranlib = self.osxcross_tools(arch)
            else:
                cc, cxx, ar, ranlib = [WINDOWS_PREFIX + suffix for suffix in ("gcc", "g++", "ar", "ranlib")]
                for tool in (cc, cxx, ar, ranlib):
                    self.make_tool(tool)
            (sdk / "plugin.mk").write_text(f"ARCH_NAME := {arch}\nall: $(DEPS_STAMP)\n")
            self.environment.update(CC=cc, CXX=cxx)
            # Seed sources through the same helper used by direct script tests.
            self.run_selection(arch)
            for origin in ("default", "environment", "command line"):
                with self.subTest(arch=arch, origin=origin):
                    override = None if origin == "default" else "ar"
                    command = [shutil.which("make"), "all", f"RACK_DIR={sdk}"]
                    environment = dict(self.environment)
                    if origin == "environment":
                        environment["AR"] = override
                    elif origin == "command line":
                        command.append(f"AR={override}")
                    result = subprocess.run(command, cwd=self.root, env=environment,
                                            capture_output=True, text=True, timeout=10)
                    self.assertEqual(result.returncode, 2, result.stdout + result.stderr)
                    self.assertIn(f"AR: {override or ar}", result.stdout.splitlines())
                    self.assertIn(f"RANLIB: {ranlib}", result.stdout.splitlines())

    def run_archive_audit(self, arch, **overrides):
        script = SCRIPT.with_name("audit-static-libraries.sh")
        prefix = self.root / "prefix"
        (prefix / "lib").mkdir(parents=True, exist_ok=True)
        for name in ("stk", "Gamma"):
            (prefix / "lib" / f"lib{name}.a").touch()
        self.make_tool("mktemp", f'exec "{shutil.which("mktemp")}" "$@"\n')
        for utility in ("rm",):
            (self.bin / utility).symlink_to(shutil.which(utility))
        self.make_tool("file", 'cat "$2"\n')
        self.make_tool("objdump", 'cat "$2"\n')
        archive_body = '''printf 'archive tool: %s\\n' "${0##*/}" >&2
case "$1" in
t) printf 'first.o\\nsecond.o\\n' ;;
p) if [ "$3" = second.o ]; then printf '%s\\n' "$SECOND_FORMAT"; else printf '%s\\n' "$FIRST_FORMAT"; fi ;;
esac
'''
        self.make_tool("ar", archive_body)
        self.make_tool(WINDOWS_PREFIX + "ar", archive_body)
        self.make_tool("nm", 'if [ "$MOCK_INDEX" = yes ]; then printf "Archive index:\\nsymbol in first.o\\n"; fi\n')
        self.make_tool("otool", 'if [ "$MOCK_INDEX" = yes ]; then printf "Table of contents from: test(__.SYMDEF)\\nsize of ranlib structures: 8 (number 1)\\n"; fi\n')
        environment = {**self.environment, "FIRST_FORMAT": "Mach-O 64-bit arm64 object",
                       "SECOND_FORMAT": "Mach-O 64-bit arm64 object", "MOCK_INDEX": "yes", **overrides}
        return subprocess.run(["/bin/sh", str(script), arch, str(prefix)], env=environment,
                              capture_output=True, text=True, timeout=10)

    def test_archive_audit_checks_every_member_and_exact_architecture(self):
        result = self.run_archive_audit("mac-arm64", SECOND_FORMAT="Mach-O 64-bit x86_64 object")
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("Wrong object format or architecture", result.stderr)
        self.assertIn("second.o", result.stderr)

    def test_archive_audit_rejects_host_format_with_same_cpu(self):
        result = self.run_archive_audit("win-x64", FIRST_FORMAT="file format elf64-x86-64")
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("Wrong object format or architecture", result.stderr)

    def test_archive_audit_rejects_missing_symbol_table(self):
        result = self.run_archive_audit("mac-arm64", MOCK_INDEX="no")
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        self.assertIn("Missing Darwin archive symbol table", result.stderr)

    def test_archive_audit_native_windows_does_not_derive_from_machine(self):
        result = self.run_archive_audit("win-x64", MACHINE=WINDOWS_PREFIX[:-1],
                                        FIRST_FORMAT="file format pe-x86-64",
                                        SECOND_FORMAT="file format pe-x86-64")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn("archive tool: " + WINDOWS_PREFIX, result.stderr)

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
