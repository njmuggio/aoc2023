#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Loc_t
{
  unsigned long y;
  unsigned long x;
} Loc;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  Loc aLocs[500];
  memset(aLocs, 0, sizeof(aLocs));
  int numLocs = 0;

  unsigned long aColOffsets[140] = {0};
  unsigned long aRowOffsets[140] = {0};

  char aEmptyRows[140];
  char aEmptyCols[140];
  memset(aEmptyRows, 1, sizeof(aEmptyRows));
  memset(aEmptyCols, 1, sizeof(aEmptyCols));

  Loc curLoc = {.y = 0, .x = 0};
  Loc gridSize = {.y = 0, .x = 0};

  int univAge = 999999;

read_next_line:
  char *pBuf = 0;
  size_t bufSize = 0;
  int lineLen = getline(&pBuf, &bufSize, pInput);
  --lineLen; // ignore newline
  {
    void *aJump[] = {&&process_input_line, &&end_of_input};
    goto *aJump[lineLen < 0];
  }

process_input_line:
  curLoc.x = 0;
process_next_char:
  char curChar = pBuf[curLoc.x];
  {
    void *aJump[] = {&&found_empty_space, &&found_galaxy};
    goto *aJump[curChar == '#'];
  }

found_galaxy:
  aLocs[numLocs++] = curLoc;
  Loc aMaxOpts[] = {gridSize, curLoc};
  gridSize.y = aMaxOpts[curLoc.y > gridSize.y].y;
  gridSize.x = aMaxOpts[curLoc.x > gridSize.x].x;
  aEmptyCols[curLoc.x] = 0;
  aEmptyRows[curLoc.y] = 0;

found_empty_space:
  curLoc.x++;
  {
    void *aJump[] = {&&process_next_char, &&end_of_line};
    goto *aJump[curLoc.x == lineLen];
  }

end_of_line:
  curLoc.y++;
  goto read_next_line;

end_of_input:
  gridSize.y++;
  gridSize.x++;

inflate_row_start:
  int curRow = 1;
inflate_row_100:
  aRowOffsets[curRow] = aRowOffsets[curRow - 1] + (aEmptyRows[curRow] * univAge);
  ++curRow;
  {
    void *aJump[] = {&&inflate_row_100, &&inflate_row_end};
    goto *aJump[curRow == gridSize.y];
  }

inflate_row_end:

inflate_col_start:
  int curCol = 1;
inflate_col_100:
  aColOffsets[curCol] = aColOffsets[curCol - 1] + (aEmptyCols[curCol] * univAge);
  ++curCol;
  {
    void *aJump[] = {&&inflate_col_100, &&inflate_col_end};
    goto *aJump[curCol == gridSize.x];
  }

inflate_col_end:

  int locAIdx = 0;
  int locBIdx = 1;
  unsigned long totalDist = 0;

inflate_col_out_lp_000:

inflate_col_in_lp_000:
  unsigned long inflatedRowOffset = labs((aLocs[locAIdx].y + aRowOffsets[aLocs[locAIdx].y]) - (aLocs[locBIdx].y + aRowOffsets[aLocs[locBIdx].y]));
  unsigned long inflatedColOffset = labs((aLocs[locAIdx].x + aColOffsets[aLocs[locAIdx].x]) - (aLocs[locBIdx].x + aColOffsets[aLocs[locBIdx].x]));
  totalDist += inflatedRowOffset + inflatedColOffset;
  // printf("%d -> %d: %d\n", locAIdx + 1, locBIdx + 1, inflatedRowOffset + inflatedColOffset);

  ++locBIdx;
  {
    void *aJump[] = {&&inflate_col_in_lp_000, &&inflate_col_in_lp_end};
    goto *aJump[locBIdx == numLocs];
  }

inflate_col_in_lp_end:
  ++locAIdx;
  locBIdx = locAIdx + 1;
  {
    void *aJump[] = {&&inflate_col_out_lp_000, &&inflate_col_out_lp_end};
    goto *aJump[locAIdx == (numLocs - 1)];
  }

inflate_col_out_lp_end:
  printf("%ld\n", totalDist);
}
