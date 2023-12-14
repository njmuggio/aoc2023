#include <stdio.h>
#include <string.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  char aGrid[100][100];
  memset(aGrid, 0, sizeof(aGrid));
  int gridHeight = 0;
  int gridWidth = 0;

read_next_line:
  int scanfResult = fscanf(pInput, "%s", aGrid[gridHeight++]);
  {
    void *aJump[] = {&&read_next_line, &&process_input};
    goto *aJump[scanfResult != 1];
  }

process_input:
  --gridHeight;
  gridWidth = gridHeight;

single_roll_step:
  int curRow = 1;
  int curCol = 0;
  int numMoved = 0;

row_lp_000:
  curCol = 0;

col_lp_000:
{
  void *aJump[] = {&&col_lp_999, &&col_lp_100};
  goto *aJump[aGrid[curRow][curCol] == 'O' && aGrid[curRow - 1][curCol] == '.'];
}

col_lp_100:
  aGrid[curRow][curCol] = '.';
  aGrid[curRow - 1][curCol] = 'O';
  numMoved = 1;

col_lp_999:
{
  void *aJump[] = {&&col_lp_000, &&row_lp_990};
  goto *aJump[++curCol == gridWidth];
}

row_lp_990:
{
  void *aJump[] = {&&row_lp_000, &&row_lp_999};
  goto *aJump[++curRow == gridHeight];
}
row_lp_999:
{
  void *aJump[] = {&&single_roll_step, &&calc_score};
  goto *aJump[numMoved == 0];
}

calc_score:
  curRow = 0;
  int totalScore = 0;

score_row_lp_000:
  curCol = 0;

score_col_lp_000:
  totalScore += (aGrid[curRow][curCol] == 'O') * (gridHeight - curRow);

score_col_lp_999:
{
  void *aJump[] = {&&score_col_lp_000, &&score_row_lp_999};
  goto *aJump[++curCol == gridWidth];
}

score_row_lp_999:
{
  void *aJump[] = {&&score_row_lp_000, &&print_score};
  goto *aJump[++curRow == gridHeight];
}

print_score:
  printf("%d\n", totalScore);
}
