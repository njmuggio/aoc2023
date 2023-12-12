#!/usr/bin/env python3

import sys

class Loc:
  def __init__(self, row: int, col: int) -> None:
    self.x = col
    self.y = row
  x: int
  y: int

locs: list[Loc] = []
emptyRows: list[bool] = [True] * 140
emptyCols: list[bool] = [True] * 140
rowOffsets: list[int] = [0] * 140
colOffsets: list[int] = [0] * 140

gridSize: Loc = Loc(0, 0)

univAge: int = 999999

with open(sys.argv[1], mode="rt", encoding="ascii") as f:
  for rowIdx, line in enumerate(f):
    for colIdx, c in enumerate(line.strip()):
      if c == '#':
        locs.append(Loc(rowIdx, colIdx))
        emptyRows[rowIdx] = False
        emptyCols[colIdx] = False
        gridSize.x = max(gridSize.x, colIdx)
        gridSize.y = max(gridSize.y, rowIdx)

gridSize.x += 1
gridSize.y += 1

for i in range(1, gridSize.y):
  rowOffsets[i] = rowOffsets[i - 1] + (emptyRows[i] * univAge)

for i in range(1, gridSize.x):
  colOffsets[i] = colOffsets[i - 1] + (emptyCols[i] * univAge)

totalDist = 0

for i in range(0, len(locs) - 1):
  for j in range(i + 1, len(locs)):
    inflatedRowOffset = abs((locs[i].y + rowOffsets[locs[i].y]) - (locs[j].y + rowOffsets[locs[j].y]))
    inflatedColOffset = abs((locs[i].x + colOffsets[locs[i].x]) - (locs[j].x + colOffsets[locs[j].x]))
    totalDist += inflatedRowOffset + inflatedColOffset

print(totalDist)
