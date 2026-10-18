#!/usr/bin/env bash

# Verify the keymap without changing the repo: generated files are up to date,
# no hand-written case is orphaned, and every board compiles.
# Usage: check.sh [--ref <git-ref>]   (default: the working tree)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/utils.sh"

QMK_DIR=$(eval echo "$(get_config '.paths.qmk_dir')")
CHECK_KEYMAP=koyo_check

BOARDS=(voyager moonlander crkbd chocofi)

# Prints the qmk compile arguments for a board
compile_args() {
    case $1 in
    voyager) echo "-kb zsa/voyager" ;;
    moonlander) echo "-kb zsa/moonlander" ;;
    crkbd) echo "-kb crkbd/rev1" ;;
    chocofi) echo "-kb crkbd/rev1 -e CONVERT_TO=rp2040_ce" ;;
    esac
}

REF=""
if [[ "${1:-}" == "--ref" ]]; then
    REF=$2
fi

WORK_DIR=$(mktemp -d)
LINK=""
cleanup() {
    [[ -n "$LINK" && -L "$LINK" ]] && rm "$LINK"
    rm -rf "$WORK_DIR"
}
trap cleanup EXIT

COPY=$WORK_DIR/repo
mkdir -p "$COPY"
if [[ -n "$REF" ]]; then
    git -C "$SCRIPT_DIR" archive "$REF" | tar -x -C "$COPY"
else
    rsync -a --exclude .git "$SCRIPT_DIR/" "$COPY/"
fi

FAILED=false
GENERATED=(assets/layout.svg)
for board in "${BOARDS[@]}"; do
    GENERATED+=("qmk/$board/src/keymap.generated.h")
done

# 1. Generated files match keymap.yml
mkdir -p "$WORK_DIR/before"
for file in "${GENERATED[@]}"; do
    mkdir -p "$WORK_DIR/before/$(dirname "$file")"
    cp "$COPY/$file" "$WORK_DIR/before/$file"
done
if ! "$COPY/update_keymap.sh" >"$WORK_DIR/update.log" 2>&1; then
    cat "$WORK_DIR/update.log"
    error_log "keymap.yml does not generate"
    exit 1
fi
STALE=false
for file in "${GENERATED[@]}"; do
    if ! cmp -s "$WORK_DIR/before/$file" "$COPY/$file"; then
        error_log "$file is out of date: run ./koyo update keymap"
        STALE=true
    fi
done
if [[ "$STALE" == "true" ]]; then
    FAILED=true
else
    success_log "Generated files match keymap.yml"
fi

# 2. Every hand-written case still matches a key in keymap.yml
ORPHANS=$(grep -ho 'case [A-Z_]*([^:]*)' "$COPY"/qmk/*/src/keymap.c | sort -u | sed 's/^case //' |
    while read -r key; do grep -qF "$key" "$COPY/keymap.yml" || echo "$key"; done)
if [[ -n "$ORPHANS" ]]; then
    while read -r key; do error_log "Orphaned case in keymap.c: $key"; done <<<"$ORPHANS"
    FAILED=true
else
    success_log "No orphaned cases in keymap.c"
fi

# 3. Every board compiles
for board in "${BOARDS[@]}"; do
    ARGS=$(compile_args "$board")
    KEYBOARD=$(echo "$ARGS" | awk '{print $2}')
    LINK=$QMK_DIR/keyboards/$KEYBOARD/keymaps/$CHECK_KEYMAP
    ln -s "$COPY/qmk/$board/src" "$LINK"
    # shellcheck disable=SC2086
    if (cd "$QMK_DIR" && qmk compile $ARGS -km "$CHECK_KEYMAP") >"$WORK_DIR/$board.log" 2>&1; then
        success_log "$board compiles"
    else
        grep -E "error|Error" "$WORK_DIR/$board.log" | head -20 || tail -20 "$WORK_DIR/$board.log"
        error_log "$board does not compile"
        FAILED=true
    fi
    rm "$LINK"
done
LINK=""

if [[ "$FAILED" == "true" ]]; then
    exit 1
fi
success_log "All checks passed"
