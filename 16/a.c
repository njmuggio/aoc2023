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

  char aGrid[112][112];
  memset(aGrid, 'X', sizeof(aGrid));
  int gridSize = 0;

  char aEnergized[112][112];
  memset(aEnergized, '.', sizeof(aEnergized));

read_next_line_000:
  size_t bufSize;
  int scanfResult = fscanf(pInput, "%s", aGrid[gridSize++ + 1] + 1);
  {
    void *aJump[] = {&&read_next_line_000, &&input_complete};
    goto *aJump[scanfResult <= 0];
  }

input_complete:
  --gridSize;

#define MAX_HEADS 100
  Head aHeads[MAX_HEADS];
  memset(aHeads, 0, sizeof(aHeads));
  aHeads[0].x = 0;
  aHeads[0].y = 1;
  aHeads[0].dx = 1;
  aHeads[0].dy = 0;
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
  printf("(%2d,%2d) %c", pCurHead->dx, pCurHead->dy, next);

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
  printf(" => traverse\n");
  // no direction changes
  goto step_cur_head_900;

step_cur_head_bounce_up:
  printf(" => bounce_up\n");
  pCurHead->dx = 0;
  pCurHead->dy = -1;
  goto step_cur_head_900;

step_cur_head_bounce_down:
  printf(" => bounce_down\n");
  pCurHead->dx = 0;
  pCurHead->dy = 1;
  goto step_cur_head_900;

step_cur_head_bounce_left:
  printf(" => bounce_left\n");
  pCurHead->dx = -1;
  pCurHead->dy = 0;
  goto step_cur_head_900;

step_cur_head_bounce_right:
  printf(" => bounce_right\n");
  pCurHead->dx = 1;
  pCurHead->dy = 0;
  goto step_cur_head_900;

step_cur_head_split_ver:
  printf(" => split_ver\n");
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
  printf(" => split_horiz\n");
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
  printf(" => terminate\n");
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

print_sum:

  printf("%d\n", totalEnergized);
}
