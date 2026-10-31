#!/bin/sh
set -eu

ARCH_NAME=$1
PREFIX=$2
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
DEPS_ROOT="$ROOT/build/deps/$ARCH_NAME"
SOURCE_ROOT="$DEPS_ROOT/src"
CACHE_ROOT="$DEPS_ROOT/downloads"
STK_COMMIT=6aacd357d76250bb7da2b1ddf675651828784bbc
GAMMA_COMMIT=88a443ba1d706ffcc4d780d47eef1fb8b847c02b
STK_SHA256=38cdcd4e494b8474a8b08e74dace857087c2068713b59c6b46d99c22af06a92c
GAMMA_SHA256=9222d22586a7c23f8851ddc8a626b334b0f016a0e010f7409bff1dd0a334f65d

CC=${CC:-cc}
CXX=${CXX:-c++}
AR=${AR:-ar}
RANLIB=${RANLIB:-ranlib}
MACHINE=${MACHINE:-}
CROSS_COMPILE=${CROSS_COMPILE:-}

find_tool() {
	tool=$1
	if ! command -v "$tool" >/dev/null 2>&1; then
		printf 'Required tool %s not found in PATH\n' "$tool" >&2
		return 1
	fi
	# Keep PATH-resolved command names intact. CMake on MSYS can misread the
	# Windows paths returned by command -v as compiler command lines.
	printf '%s' "$tool"
}

AR_BIN=$AR

mkdir -p "$SOURCE_ROOT" "$CACHE_ROOT" "$PREFIX"
PREFIX=$(CDPATH= cd -- "$PREFIX" && pwd)

sha256() {
	if command -v shasum >/dev/null 2>&1; then
		printf '%s  %s\n' "$2" "$1" | shasum -a 256 -c - >/dev/null
	else
		printf '%s  %s\n' "$2" "$1" | sha256sum -c - >/dev/null
	fi
}

fetch_source() {
	name=$1
	commit=$2
	sha=$3
	archive="$CACHE_ROOT/$name-$commit.tar.gz"
	target="$SOURCE_ROOT/$name"
	if [ ! -f "$archive" ]; then
		curl -fsSL "https://github.com/$4/$name/archive/$commit.tar.gz" -o "$archive"
	fi
	sha256 "$archive" "$sha"
	if [ ! -f "$target/.source-commit" ] || [ "$(cat "$target/.source-commit" 2>/dev/null || true)" != "$commit" ]; then
		rm -rf "$target"
		tar -xzf "$archive" -C "$SOURCE_ROOT"
		extracted=$(tar -tzf "$archive" | sed -n '1s,/.*,,p')
		mv "$SOURCE_ROOT/$extracted" "$target"
		printf '%s\n' "$commit" > "$target/.source-commit"
	fi
}

fetch_source stk "$STK_COMMIT" "$STK_SHA256" thestk
fetch_source Gamma "$GAMMA_COMMIT" "$GAMMA_SHA256" LancePutnam

case "$ARCH_NAME" in
	mac-x64|mac-arm64)
		platform=Darwin
		gamma_platform=macosx
		target_flags=""
		# Keep Rack's tools, using the defaults above for empty values.
		;;
	win-x64)
		platform=Windows
		gamma_platform=windows
		target_flags=""
		# Rack sets MACHINE to CROSS_COMPILE for cross builds. In native MSYS2
		# builds MACHINE is the MinGW target triple while CC/CXX are commonly
		# gcc/g++; prefer the explicit prefix, then triple-prefixed tools if
		# available, and otherwise retain Rack's compiler commands.
		if [ -n "$CROSS_COMPILE" ]; then
			CC="${CROSS_COMPILE}gcc"
			CXX="${CROSS_COMPILE}g++"
			AR_BIN="${CROSS_COMPILE}ar"
			RANLIB="${CROSS_COMPILE}ranlib"
		elif [ -n "$MACHINE" ] && command -v "${MACHINE}-gcc" >/dev/null 2>&1; then
			CC="${MACHINE}-gcc"
			CXX="${MACHINE}-g++"
			AR_BIN="${MACHINE}-ar"
			RANLIB="${MACHINE}-ranlib"
		fi
		;;
	lin-x64)
		platform=Linux
		gamma_platform=linux
		target_flags=""
		AR_BIN=$(command -v x86_64-ubuntu16.04-linux-gnu-ar)
		RANLIB=$(command -v x86_64-ubuntu16.04-linux-gnu-ranlib)
		;;
	*)
		echo "Unsupported dependency target: $ARCH_NAME" >&2
		exit 2
		;;
esac

printf 'Dependency target: %s\nCC: %s\nCXX: %s\nAR: %s\nRANLIB: %s\nMACHINE: %s\nCROSS_COMPILE: %s\n' \
	"$ARCH_NAME" "$CC" "$CXX" "$AR_BIN" "$RANLIB" "$MACHINE" "$CROSS_COMPILE"
CC=$(find_tool "$CC")
CXX=$(find_tool "$CXX")
AR_BIN=$(find_tool "$AR_BIN")
RANLIB=$(find_tool "$RANLIB")
AR_PATH=$(command -v "$AR_BIN")
RANLIB_PATH=$(command -v "$RANLIB")

if [ "$ARCH_NAME" = win-x64 ] && [ -n "$MACHINE" ]; then
	compiler_target=$($CC -dumpmachine 2>/dev/null || true)
	case "$compiler_target" in
		*mingw32*) ;;
		*) printf 'Compiler %s does not target Windows (reported %s; MACHINE=%s)\n' "$CC" "${compiler_target:-unknown}" "$MACHINE" >&2; exit 1 ;;
	esac
fi


stk_build="$DEPS_ROOT/stk-build"
# The upstream CMake file globs realtime/network sources even when REALTIME is
# disabled. Keep the archive minimal and platform-independent for this plugin.
if ! grep -q 'set(STK_SRC' "$SOURCE_ROOT/stk/CMakeLists.txt"; then
	perl -0pi -e 's/file\(GLOB STK_SRC "\.\/src\/\*\.cpp"\)/set(STK_SRC "\.\/src\/Stk.cpp;\.\/src\/Chorus.cpp;\.\/src\/NRev.cpp;\.\/src\/DelayL.cpp;\.\/src\/Delay.cpp;\.\/src\/SineWave.cpp;\.\/src\/OnePole.cpp")/' "$SOURCE_ROOT/stk/CMakeLists.txt"
fi
cmake_generator=${CMAKE_GENERATOR:-Unix Makefiles}
cmake -S "$SOURCE_ROOT/stk" -B "$stk_build" -G "$cmake_generator" \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_SYSTEM_NAME="$platform" \
	-DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 \
	-DCMAKE_C_COMPILER="$CC" -DCMAKE_CXX_COMPILER="$CXX" \
	-DCMAKE_AR="$AR_PATH" -DCMAKE_RANLIB="$RANLIB_PATH" \
	-DCMAKE_C_FLAGS="$target_flags -fPIC" \
	-DCMAKE_CXX_FLAGS="$target_flags -fPIC" \
	-DCMAKE_POSITION_INDEPENDENT_CODE=ON \
	-DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
	-DBUILD_SHARED=OFF -DBUILD_STATIC=ON -DREALTIME=OFF \
	-DENABLE_JACK=OFF -DENABLE_ALSA=OFF -DCOMPILE_PROJECTS=OFF \
	-DCMAKE_INSTALL_PREFIX="$PREFIX" -DCMAKE_INSTALL_LIBDIR=lib
cmake --build "$stk_build" --target install --parallel
"$RANLIB" "$PREFIX/lib/libstk.a"


gamma_build="$DEPS_ROOT/gamma-build"
gamma_objects="$gamma_build/obj"
mkdir -p "$gamma_objects" "$PREFIX/lib" "$PREFIX/include"
gamma_sources="arr Conversion Domain DFT FFT_fftpack fftpack++1 fftpack++2 Print scl Recorder Scheduler Timer"
(
	cd "$DEPS_ROOT"
	gamma_objects_list=
	for source_name in $gamma_sources; do
		object="gamma-build/obj/$source_name.o"
		"$CXX" -c -I"$SOURCE_ROOT/Gamma" -I"$SOURCE_ROOT/Gamma/Gamma" \
			-DNDEBUG -DGAM_NO_AUDIO_IO $target_flags -fPIC -std=c++14 \
			"$SOURCE_ROOT/Gamma/src/$source_name.cpp" -o "$object"
		gamma_objects_list="$gamma_objects_list $object"
	done
	"$AR_BIN" crs "$PREFIX/lib/libGamma.a" $gamma_objects_list
	"$RANLIB" "$PREFIX/lib/libGamma.a"
)
cp -R "$SOURCE_ROOT/Gamma/Gamma" "$PREFIX/include/"
cp -R "$SOURCE_ROOT/Gamma/Gamma" "$PREFIX/include/"

printf '%s\n' "$ARCH_NAME $STK_COMMIT $GAMMA_COMMIT" > "$DEPS_ROOT/.built"
