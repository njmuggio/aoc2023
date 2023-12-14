#include <stdio.h>
#include <string.h>

typedef struct Snapshot_t
{
  char aGrid[100][100];
  int snapshotIdx;
  int northLoad;
} Snapshot;

Snapshot aSnapshots[1000];

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  char aGrid[100][100];
  memset(aGrid, 0, sizeof(aGrid));
  int gridHeight = 0;
  int gridWidth = 0;

  int currentCycle = -1;

  memset(aSnapshots, 0, sizeof(aSnapshots));
  int numStateSnapshots = 0;

read_next_line:
  int scanfResult = fscanf(pInput, "%s", aGrid[gridHeight++]);
  {
    void *aJump[] = {&&read_next_line, &&process_input};
    goto *aJump[scanfResult != 1];
  }

process_input:
  --gridHeight;
  gridWidth = gridHeight;

next_cycle:
  ++currentCycle;

north_single_roll_step:
  int curRow = 1;
  int curCol = 0;
  int numMoved = 0;

north_row_lp_000:
  curCol = 0;

north_col_lp_000:
{
  void *aJump[] = {&&north_col_lp_999, &&north_col_lp_100};
  goto *aJump[aGrid[curRow][curCol] == 'O' && aGrid[curRow - 1][curCol] == '.'];
}

north_col_lp_100:
  aGrid[curRow][curCol] = '.';
  aGrid[curRow - 1][curCol] = 'O';
  numMoved = 1;

north_col_lp_999:
{
  void *aJump[] = {&&north_col_lp_000, &&north_row_lp_990};
  goto *aJump[++curCol == gridWidth];
}

north_row_lp_990:
{
  void *aJump[] = {&&north_row_lp_000, &&north_row_lp_999};
  goto *aJump[++curRow == gridHeight];
}
north_row_lp_999:
{
  void *aJump[] = {&&north_single_roll_step, &&west_single_roll_step};
  goto *aJump[numMoved == 0];
}

west_single_roll_step:
  curRow = 0;
  curCol = 1;
  numMoved = 0;

west_row_lp_000:
  curCol = 1;

west_col_lp_000:
{
  void *aJump[] = {&&west_col_lp_999, &&west_col_lp_100};
  goto *aJump[aGrid[curRow][curCol] == 'O' && aGrid[curRow][curCol - 1] == '.'];
}

west_col_lp_100:
  aGrid[curRow][curCol] = '.';
  aGrid[curRow][curCol - 1] = 'O';
  numMoved = 1;

west_col_lp_999:
{
  void *aJump[] = {&&west_col_lp_000, &&west_row_lp_990};
  goto *aJump[++curCol == gridWidth];
}

west_row_lp_990:
{
  void *aJump[] = {&&west_row_lp_000, &&west_row_lp_999};
  goto *aJump[++curRow == gridHeight];
}
west_row_lp_999:
{
  void *aJump[] = {&&west_single_roll_step, &&south_single_roll_step};
  goto *aJump[numMoved == 0];
}

south_single_roll_step:
  curRow = 0;
  curCol = 0;
  numMoved = 0;

south_row_lp_000:
  curCol = 0;

south_col_lp_000:
{
  void *aJump[] = {&&south_col_lp_999, &&south_col_lp_100};
  goto *aJump[aGrid[curRow][curCol] == 'O' && aGrid[curRow + 1][curCol] == '.'];
}

south_col_lp_100:
  aGrid[curRow][curCol] = '.';
  aGrid[curRow + 1][curCol] = 'O';
  numMoved = 1;

south_col_lp_999:
{
  void *aJump[] = {&&south_col_lp_000, &&south_row_lp_990};
  goto *aJump[++curCol == gridWidth];
}

south_row_lp_990:
{
  void *aJump[] = {&&south_row_lp_000, &&south_row_lp_999};
  goto *aJump[++curRow == (gridHeight - 1)];
}
south_row_lp_999:
{
  void *aJump[] = {&&south_single_roll_step, &&east_single_roll_step};
  goto *aJump[numMoved == 0];
}

east_single_roll_step:
  curRow = 0;
  curCol = 0;
  numMoved = 0;

east_row_lp_000:
  curCol = 0;

east_col_lp_000:
{
  void *aJump[] = {&&east_col_lp_999, &&east_col_lp_100};
  goto *aJump[aGrid[curRow][curCol] == 'O' && aGrid[curRow][curCol + 1] == '.'];
}

east_col_lp_100:
  aGrid[curRow][curCol] = '.';
  aGrid[curRow][curCol + 1] = 'O';
  numMoved = 1;

east_col_lp_999:
{
  void *aJump[] = {&&east_col_lp_000, &&east_row_lp_990};
  goto *aJump[++curCol == (gridWidth - 1)];
}

east_row_lp_990:
{
  void *aJump[] = {&&east_row_lp_000, &&east_row_lp_999};
  goto *aJump[++curRow == (gridHeight)];
}
east_row_lp_999:
{
  void *aJump[] = {&&east_single_roll_step, &&eval_current_cycle};
  goto *aJump[numMoved == 0];
}

eval_current_cycle:
  int curSnapshot = -1;
compare_next_snapshot_000:
  ++curSnapshot;
  {
    void *aJump[] = {&&compare_next_snapshot_100, &&store_new_snapshot};
    goto *aJump[curSnapshot == numStateSnapshots];
  }
compare_next_snapshot_100:
  int cmp = memcmp(aSnapshots[curSnapshot].aGrid, aGrid, sizeof(aGrid));
  {
    void *aJump[] = {&&compare_next_snapshot_000, &&found_repeat_state};
    goto *aJump[cmp == 0];
  }

store_new_snapshot:
  memcpy(aSnapshots[numStateSnapshots].aGrid, aGrid, sizeof(aGrid));
  aSnapshots[numStateSnapshots].snapshotIdx = numStateSnapshots;
  // printf("Cycle %d done\n", currentCycle);

calc_score:
  curRow = 0;

score_row_lp_000:
  curCol = 0;

score_col_lp_000:
  aSnapshots[numStateSnapshots].northLoad += (aGrid[curRow][curCol] == 'O') * (gridHeight - curRow);

score_col_lp_999:
{
  void *aJump[] = {&&score_col_lp_000, &&score_row_lp_990};
  goto *aJump[++curCol == gridWidth];
}

score_row_lp_990:
{
  void *aJump[] = {&&score_row_lp_000, &&score_row_lp_999};
  goto *aJump[++curRow == gridHeight];
}

score_row_lp_999:
  ++numStateSnapshots;
  goto next_cycle;

found_repeat_state:
  int cycleSize = currentCycle - curSnapshot;
  int targetCycle = 999999999;

  printf("%d\n", aSnapshots[(targetCycle - curSnapshot) % cycleSize + curSnapshot].northLoad);
}
