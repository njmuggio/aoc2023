#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct Head_t
{
  int x;
  int y;
  int dx;
  int dy;
} Head;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  char aBackupGrid[112][112];

  char aGrid[112][112];
  memset(aGrid, 'X', sizeof(aGrid));
  int gridSize = 0;

  char aEnergized[112][112];
  memset(aEnergized, '.', sizeof(aEnergized));

  int maxEnergized = 0;

read_next_line_000:
  size_t bufSize;
  int scanfResult = fscanf(pInput, "%s", aGrid[gridSize++ + 1] + 1);
  {
    void *aJump[] = {&&read_next_line_000, &&input_complete};
    goto *aJump[scanfResult <= 0];
  }

input_complete:
  memcpy(aBackupGrid, aGrid, sizeof(aGrid));
  --gridSize;
  void *pNextStartPoint = 0;

from_top:
  int startCol = 0;
  int startRow = 0;
  int startDx = 0;
  int startDy = 1;
from_top_lp:
{
  void *pNextStartPointOpts[] = {&&from_top_lp, &&from_right};
  pNextStartPoint = pNextStartPointOpts[startCol++ == gridSize];
}
  goto process_grid;

from_right:
  startCol = gridSize + 1;
  startRow = 1;
  startDx = -1;
  startDy = 0;
from_right_lp:
{
  void *pNextStartPointOpts[] = {&&from_right_lp, &&from_left};
  pNextStartPoint = pNextStartPointOpts[startRow++ == gridSize];
}
  goto process_grid;

from_left:
  startCol = 1;
  startRow = 1;
  startDx = 1;
  startDy = 0;
from_left_lp:
{
  void *pNextStartPointOpts[] = {&&from_left_lp, &&from_bottom};
  pNextStartPoint = pNextStartPointOpts[startRow++ == gridSize];
}
  goto process_grid;

from_bottom:
  startCol = 1;
  startRow = gridSize + 1;
  startDx = 0;
  startDy = -1;
from_bottom_lp:
{
  void *pNextStartPointOpts[] = {&&from_bottom_lp, &&print_max};
  pNextStartPoint = pNextStartPointOpts[startCol++ == gridSize];
}
  goto process_grid;

process_grid:
#define MAX_HEADS 100
  Head aHeads[MAX_HEADS];
  memset(aHeads, 0, sizeof(aHeads));
  aHeads[0].x = startCol;
  aHeads[0].y = startRow;
  aHeads[0].dx = startDx;
  aHeads[0].dy = startDy;
  int numHeads = 1;

step_all_heads_000:
{
  void *aJump[] = {&&step_all_heads_100, &&no_more_laser};
  goto *aJump[numHeads == 0];
}

step_all_heads_100:
  int curHead = numHeads - 1;
step_cur_head_000:
  Head *pCurHead = &aHeads[curHead];
  char next = aGrid[pCurHead->y + pCurHead->dy][pCurHead->x + pCurHead->dx];

  pCurHead->x += pCurHead->dx;
  pCurHead->y += pCurHead->dy;
  aEnergized[pCurHead->y][pCurHead->x] = '#';
  // printf("(%2d,%2d) %c", pCurHead->dx, pCurHead->dy, next);

  {
    void *aJump[] = {
        &&step_cur_head_traverse,
        &&step_cur_head_bounce_up,
        &&step_cur_head_bounce_down,
        &&step_cur_head_bounce_left,
        &&step_cur_head_bounce_right,
        &&step_cur_head_split_ver,
        &&step_cur_head_split_horiz,
        &&step_cur_head_terminate};
    int traverse = next == '.' || (pCurHead->dx != 0 && next == '-') || (pCurHead->dy != 0 && next == '|');
    int bounceUp = (next == '/' && pCurHead->dx == 1) || (next == '\\' && pCurHead->dx == -1);
    int bounceDown = (next == '/' && pCurHead->dx == -1) || (next == '\\' && pCurHead->dx == 1);
    int bounceLeft = (next == '/' && pCurHead->dy == 1) || (next == '\\' && pCurHead->dy == -1);
    int bounceRight = (next == '/' && pCurHead->dy == -1) || (next == '\\' && pCurHead->dy == 1);
    int splitVer = (next == '|' && pCurHead->dx != 0);
    int splitHoriz = (next == '-' && pCurHead->dy != 0);
    int terminate = (next == 'X' || next == 0);
    assert((traverse + bounceUp + bounceDown + bounceLeft + bounceRight + splitVer + splitHoriz + terminate) == 1);
    goto *aJump[0 * traverse + 1 * bounceUp + 2 * bounceDown + 3 * bounceLeft + 4 * bounceRight + 5 * splitVer + 6 * splitHoriz + 7 * terminate];
  }

step_cur_head_traverse:
  // printf(" => traverse\n");
  // no direction changes
  goto step_cur_head_900;

step_cur_head_bounce_up:
  // printf(" => bounce_up\n");
  pCurHead->dx = 0;
  pCurHead->dy = -1;
  goto step_cur_head_900;

step_cur_head_bounce_down:
  // printf(" => bounce_down\n");
  pCurHead->dx = 0;
  pCurHead->dy = 1;
  goto step_cur_head_900;

step_cur_head_bounce_left:
  // printf(" => bounce_left\n");
  pCurHead->dx = -1;
  pCurHead->dy = 0;
  goto step_cur_head_900;

step_cur_head_bounce_right:
  // printf(" => bounce_right\n");
  pCurHead->dx = 1;
  pCurHead->dy = 0;
  goto step_cur_head_900;

step_cur_head_split_ver:
  // printf(" => split_ver\n");
  aGrid[pCurHead->y][pCurHead->x] = 'X';
  pCurHead->dx = 0;
  pCurHead->dy = -1;

  assert(numHeads < MAX_HEADS);
  aHeads[numHeads].x = pCurHead->x;
  aHeads[numHeads].y = pCurHead->y;
  aHeads[numHeads].dx = 0;
  aHeads[numHeads++].dy = 1;

  goto step_cur_head_900;

step_cur_head_split_horiz:
  // printf(" => split_horiz\n");
  aGrid[pCurHead->y][pCurHead->x] = 'X';
  pCurHead->dx = -1;
  pCurHead->dy = 0;

  assert(numHeads < MAX_HEADS);
  aHeads[numHeads].x = pCurHead->x;
  aHeads[numHeads].y = pCurHead->y;
  aHeads[numHeads].dx = 1;
  aHeads[numHeads++].dy = 0;

  goto step_cur_head_900;

step_cur_head_terminate:
  // printf(" => terminate\n");
  --numHeads;

step_cur_head_900:
  goto step_all_heads_000;

no_more_laser:
  int totalEnergized = 0;
  int curRow = 0;
  int curCol = 0;
sum_row_lp:
  curCol = 0;
sum_col_lp:
  totalEnergized += aEnergized[curRow + 1][curCol + 1] == '#';
  {
    void *aJump[] = {&&sum_col_lp, &&sum_col_lp_end};
    goto *aJump[++curCol == gridSize];
  }
sum_col_lp_end:
  curCol = 0;
  {
    void *aJump[] = {&&sum_row_lp, &&sum_row_lp_end};
    goto *aJump[++curRow == gridSize];
  }
sum_row_lp_end:

  memset(aEnergized, '.', sizeof(aEnergized));
  memcpy(aGrid, aBackupGrid, sizeof(aGrid));
  int aMaxOptions[] = {maxEnergized, totalEnergized};
  maxEnergized = aMaxOptions[totalEnergized > maxEnergized];
  goto *pNextStartPoint;

print_max:
  printf("%d\n", maxEnergized);
}
