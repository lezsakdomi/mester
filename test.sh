#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 test-id [feladat-nev]" >&2
    echo "Note: feladat-nev can be supplied using \$NAME" >&2
    exit 2
fi

ID="$1"
NAME="${2:-$NAME}"
TOOL="${TOOL:-run}"
TOOL="${3:-$TOOL}"

unzip -p "$NAME.zip" "be$ID.txt" >"$NAME.txt"
jam "$TOOL-$NAME"
echo -------------------------
unzip -p "$NAME.zip" "ki$ID.txt" | tee "$NAME.txt.sample"
