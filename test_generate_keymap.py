"""Check that board_rows puts each keymap.yml key where its board expects it."""

import unittest

from generate_keymap import NO, board_rows

TOP = [f"T{i}" for i in range(12)]
R1 = [f"A{i}" for i in range(12)]
R2 = [f"B{i}" for i in range(12)]
R3 = [f"C{i}" for i in range(12)]
THUMBS = ["TL0", "TL1", "TR0", "TR1"]
ROWS = [TOP, R1, R2, R3, THUMBS]


class BoardRows(unittest.TestCase):
    def test_voyager_keeps_the_keymap_shape(self):
        self.assertEqual(board_rows("voyager", ROWS), ROWS)

    def test_moonlander_adds_inner_columns_and_thumb_gaps(self):
        rows = board_rows("moonlander", ROWS)
        self.assertEqual([len(r) for r in rows], [14, 14, 14, 12, 12, 6])
        self.assertEqual(rows[0][5:9], ["T5", NO, NO, "T6"])
        self.assertEqual(rows[2][0], "B0")
        self.assertEqual(rows[2][13], "B11")
        self.assertEqual(rows[3], R3)
        self.assertEqual(rows[4], [NO] * 12)
        self.assertEqual(rows[5], ["TL0", "TL1", NO, NO, "TR0", "TR1"])

    def test_corne_and_chocofi_take_the_core_and_thumbs(self):
        for board in ("crkbd", "chocofi"):
            rows = board_rows(board, ROWS)
            self.assertEqual(rows[0], R1[1:11])
            self.assertEqual(rows[1], R2[1:11])
            self.assertEqual(rows[2], R3[1:11])
            self.assertEqual(rows[3], [NO, "TL0", "TL1", "TR0", "TR1", NO])


if __name__ == "__main__":
    unittest.main()
