"""Generate board headers and drawing input from keymap.yml.

`generate_keymap.py <repo> <out_dir>` reads keymap.yml as JSON on stdin (converted by yq) and writes:
- qmk/<board>/src/keymap.generated.h for every board
- <out_dir>/keymap.json, a QMK keymap.json in the Voyager shape for `keymap parse`
- <out_dir>/layer_names.txt and <out_dir>/combos.json for the drawing

`generate_keymap.py combos <out_dir>` reads the parsed combo-label layer as JSON on stdin
and writes <out_dir>/drawing_combos.json.
"""

import json
import re
import sys
from pathlib import Path

NO = "KC_NO"

# How each board's LAYOUT macro is filled from the 52 keys of keymap.yml:
# rows 0-3 hold twelve keys (outer, core x5 | core x5, outer), row 4 the four thumbs.
BOARDS = {
    "voyager": "LAYOUT_voyager",
    "moonlander": "LAYOUT_moonlander",
    "crkbd": "LAYOUT_split_3x5_3",
    "chocofi": "LAYOUT_split_3x5_3",
}


def split_top(text, sep):
    parts, depth, cur = [], 0, ""
    for ch in text:
        depth += {"(": 1, ")": -1}.get(ch, 0)
        if ch == sep and depth == 0:
            parts.append(cur.strip())
            cur = ""
        else:
            cur += ch
    parts.append(cur.strip())
    return parts


def parse_row(row):
    keys = [k for half in split_top(row, "|") for k in split_top(half, ",")]
    return [NO if k == "XXXXXXX" else k for k in keys]


def board_rows(board, rows):
    """Arrange the five keymap.yml rows into the board's LAYOUT rows."""
    top, r1, r2, r3, thumbs = rows
    if board == "voyager":
        return [top, r1, r2, r3, thumbs]
    if board == "moonlander":
        inner = [NO, NO]
        return [
            top[:6] + inner + top[6:],
            r1[:6] + inner + r1[6:],
            r2[:6] + inner + r2[6:],
            r3,
            [NO] * 12,
            thumbs[:2] + [NO, NO] + thumbs[2:],
        ]
    return [r1[1:11], r2[1:11], r3[1:11], [NO] + thumbs + [NO]]


def mentions(text, layers):
    return any(re.search(rf"\b{name}\b", text) for name in layers)


def c_rows(rows):
    widths = {}
    for row in rows:
        for i, key in enumerate(row):
            widths[len(row), i] = max(widths.get((len(row), i), 0), len(key))
    lines = []
    for row in rows:
        cells = [key.ljust(widths[len(row), i]) for i, key in enumerate(row)]
        lines.append("  " + " , ".join(cells).rstrip())
    return ",\n".join(lines)


def header(board, layers, combos):
    names = [n for n, l in layers.items() if board in l.get("boards", BOARDS)]
    missing = [n for n in layers if n not in names]
    out = [
        "// Generated from keymap.yml by `./koyo update keymap`. Edit keymap.yml, never this file.",
        "#pragma once",
        "",
        "enum layers {",
        *[f"    {n}," for n in names],
        "};",
        "",
        "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {",
    ]
    for name in names:
        rows = [[NO if mentions(k, missing) else k for k in parse_row(r)] for r in layers[name]["rows"]]
        out += [f"[{name}] = {BOARDS[board]}(", c_rows(board_rows(board, rows)), "),", ""]
    out[-1] = "};"
    out.append("")
    entries = []
    for cname, combo in combos.items():
        if combo["layer"] not in names or mentions(combo["keys"] + combo["send"], missing):
            continue
        array = f"{combo['layer']}_CMB_{cname}"
        out.append(f"const uint16_t PROGMEM {array}[] = {{{', '.join(split_top(combo['keys'], ','))}, COMBO_END}};")
        entries.append(f"    COMBO({array}, {combo['send']}),")
    out += ["", "combo_t key_combos[] = {", *entries, "};", ""]
    return "\n".join(out)


# keymap-drawer labels keys it parses; this extra layer carries the combo outputs
# through the parser so their labels match the keys', and is removed afterwards.
COMBO_LAYER = "COMBO_LABELS"


def drawing(layers, combos, out_dir):
    names = list(layers)
    index = {n: str(i) for i, n in enumerate(names)}

    def for_drawing(key):
        # keymap-drawer reads layers by index and shows clean holds only for short mod-taps
        key = re.sub(r"\bLY_\w+\b", lambda m: index[m.group(0)], key)
        return re.sub(r"MT\(MOD_(\w+),\s*", r"\1_T(", key)

    flat = {n: [k for r in l["rows"] for k in parse_row(r)] for n, l in layers.items()}
    labels = {
        n: f"{n} ({', '.join(b.capitalize() for b in l['boards'])} only)" if l.get("boards") else n
        for n, l in layers.items()
    }
    sends = [for_drawing(c["send"]) for c in combos.values()]
    keymap = {
        "keyboard": "zsa/voyager",
        "layout": "LAYOUT",
        "layers": [[for_drawing(k) for k in flat[n]] for n in names]
        + [sends + [NO] * (52 - len(sends))],
    }
    (out_dir / "keymap.json").write_text(json.dumps(keymap, indent=1))

    placements = []
    for cname, combo in combos.items():
        layer = [k.replace(" ", "") for k in flat[combo["layer"]]]
        positions = []
        for key in split_top(combo["keys"], ","):
            if key.replace(" ", "") not in layer:
                sys.exit(f"combo {cname}: {key} is not on {combo['layer']}")
            positions.append(layer.index(key.replace(" ", "")))
        placements.append({"p": positions, "l": labels[combo["layer"]]})
    (out_dir / "combos.json").write_text(json.dumps(placements))

    (out_dir / "layer_names.txt").write_text("\n".join([*labels.values(), COMBO_LAYER]) + "\n")


def combos_for_drawing(out_dir):
    """Pair the parsed combo-label layer (JSON on stdin) with the combo placements."""
    labels = json.load(sys.stdin)
    placements = json.loads((out_dir / "combos.json").read_text())
    combos = [{"p": c["p"], "k": label, "l": [c["l"]]} for c, label in zip(placements, labels)]
    (out_dir / "drawing_combos.json").write_text(json.dumps(combos))


def main():
    if sys.argv[1] == "combos":
        combos_for_drawing(Path(sys.argv[2]))
        return
    repo, out_dir = Path(sys.argv[1]), Path(sys.argv[2])
    data = json.load(sys.stdin)
    layers, combos = data["layers"], data.get("combos", {})
    for name, layer in layers.items():
        rows = [parse_row(r) for r in layer["rows"]]
        if [len(r) for r in rows] != [12, 12, 12, 12, 4]:
            sys.exit(f"{name}: expected rows of 12, 12, 12, 12 and 4 keys, got {[len(r) for r in rows]}")
        if unknown := set(layer.get("boards", [])) - set(BOARDS):
            sys.exit(f"{name}: unknown boards {sorted(unknown)}, expected some of {list(BOARDS)}")
    for cname, combo in combos.items():
        if combo["layer"] not in layers:
            sys.exit(f"combo {cname}: unknown layer {combo['layer']}")
    drawing(layers, combos, out_dir)
    for board in BOARDS:
        (repo / "qmk" / board / "src" / "keymap.generated.h").write_text(header(board, layers, combos))


if __name__ == "__main__":
    main()
