#!/bin/sh
set -eu

ARCH_NAME=$1
PREFIX=$2
AR=${AR:-ar}
case "$AR" in */*) ;; *) AR=$(command -v "$AR") ;; esac
case "$ARCH_NAME" in
	mac-x64) expected=x86_64 ;;
	mac-arm64) expected=arm64 ;;
	lin-x64|win-x64) expected=x86-64 ;;
	*) echo "Unsupported audit target: $ARCH_NAME" >&2; exit 2 ;;
esac

for library in "$PREFIX/lib/libstk.a" "$PREFIX/lib/libGamma.a"; do
	[ -f "$library" ] || { echo "Missing static library: $library" >&2; exit 1; }
	if command -v lipo >/dev/null 2>&1 && [ "$ARCH_NAME" != lin-x64 ] && [ "$ARCH_NAME" != win-x64 ]; then
		info=$(lipo -info "$library")
		echo "$info"
		echo "$info" | grep -q "$expected" || { echo "Wrong architecture in $library" >&2; exit 1; }
	else
		member=$("$AR" t "$library" | sed -n '1p')
		tmp=$(mktemp)
		trap 'rm -f "$tmp"' EXIT HUP INT TERM
		"$AR" p "$library" "$member" > "$tmp"
		info=$(file "$tmp")
		echo "$library: $info"
		echo "$info" | grep -Eiq "$expected|x86_64|amd64" || { echo "Wrong architecture in $library" >&2; exit 1; }
		rm -f "$tmp"
		trap - EXIT HUP INT TERM
	fi
done
