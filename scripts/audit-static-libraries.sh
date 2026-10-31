#!/bin/sh
set -eu

ARCH_NAME=$1
PREFIX=$2
CC=${CC:-cc}
supplied_ar=${AR:-}
AR=${AR:-ar}
NM=${NM:-nm}
OTOOL=${OTOOL:-otool}
OBJDUMP=${OBJDUMP:-objdump}
CROSS_COMPILE=${CROSS_COMPILE:-}

# Match the dependency builder without interpreting MACHINE as a tool prefix.
compiler=${CC##*/}
toolchain_prefix=
case "$ARCH_NAME:$compiler" in
	mac-*:*-apple-darwin*-clang) toolchain_prefix=${compiler%-clang} ;;
	win-x64:*)
		if [ -n "$CROSS_COMPILE" ]; then
			toolchain_prefix=${CROSS_COMPILE%-}
			AR="${CROSS_COMPILE}ar"
		else
			case "$compiler" in
				*-mingw32-gcc|*-mingw32-clang) toolchain_prefix=${compiler%-*} ;;
			esac
		fi
		;;
	lin-x64:*) toolchain_prefix=x86_64-ubuntu16.04-linux-gnu ;;
esac
if [ -n "$toolchain_prefix" ]; then
	if [ -z "$supplied_ar" ] && command -v "$toolchain_prefix-ar" >/dev/null 2>&1; then
		AR="$toolchain_prefix-ar"
	fi
	if command -v "$toolchain_prefix-nm" >/dev/null 2>&1; then
		NM="$toolchain_prefix-nm"
	fi
	if command -v "$toolchain_prefix-otool" >/dev/null 2>&1; then
		OTOOL="$toolchain_prefix-otool"
	fi
	if command -v "$toolchain_prefix-objdump" >/dev/null 2>&1; then
		OBJDUMP="$toolchain_prefix-objdump"
	fi
fi
case "$ARCH_NAME" in
	mac-arm64) expected='Mach-O 64-bit.*arm64' ;;
	mac-x64) expected='Mach-O 64-bit.*x86_64' ;;
	lin-x64) expected='file format elf64-x86-64' ;;
	win-x64) expected='file format pe-x86-64' ;;
	*) echo "Unsupported audit target: $ARCH_NAME" >&2; exit 2 ;;
esac

command -v "$AR" >/dev/null 2>&1 || { echo "Archive tool $AR not found in PATH" >&2; exit 1; }
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT HUP INT TERM
for library in "$PREFIX/lib/libstk.a" "$PREFIX/lib/libGamma.a"; do
	[ -f "$library" ] || { echo "Missing static library: $library" >&2; exit 1; }
	case "$ARCH_NAME" in
		mac-*)
			"$OTOOL" -Sv "$library" > "$tmp/index"
			grep -q 'Table of contents from:.*(__.SYMDEF' "$tmp/index" &&
				grep -Eq 'number [1-9][0-9]*' "$tmp/index" || {
				echo "Missing Darwin archive symbol table in $library" >&2; exit 1;
			}
			;;
		*)
			"$NM" -s "$library" > "$tmp/index"
			grep -q '^Archive index:' "$tmp/index" || {
				echo "Missing archive symbol table in $library" >&2; exit 1;
			}
			;;
	esac
	"$AR" t "$library" > "$tmp/members"
	count=0
	while IFS= read -r member; do
		case "$member" in __.SYMDEF*|'/'|'//') continue ;; esac
		"$AR" p "$library" "$member" > "$tmp/object"
		case "$ARCH_NAME" in
			mac-*) info=$(file -b "$tmp/object") ;;
			# file(1) can misidentify large COFF objects as unrelated data.
			*) info=$("$OBJDUMP" -f "$tmp/object") ;;
		esac
		printf '%s(%s): %s\n' "$library" "$member" "$info"
		printf '%s\n' "$info" | grep -Eq "$expected" || {
			echo "Wrong object format or architecture in $library($member)" >&2; exit 1;
		}
		count=$((count + 1))
	done < "$tmp/members"
	[ "$count" -gt 0 ] || { echo "Empty archive: $library" >&2; exit 1; }
	printf '%s: valid symbol table; %s target objects checked\n' "$library" "$count"
done
