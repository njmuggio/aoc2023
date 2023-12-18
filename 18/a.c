#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct Inst_t
{
  union
  {
    char aDir[2];
    char dir;
  };
  int len;
  int color;
} Inst;

typedef struct Coord_t
{
  int x;
  int y;
} Coord;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

#define GRID_SIZE 750
  char aMap[GRID_SIZE][GRID_SIZE];
  memset(aMap, '.', sizeof(aMap));

  Inst aInst[700];
  Inst *pInstEnd = &aInst[0];

read_input:
  int scanfResult = fscanf(pInput, "%1s %d (#%x)", pInstEnd->aDir, &pInstEnd->len, &pInstEnd->color);
  ++pInstEnd;
  {
    void *aJump[] = {&&read_input, &&end_of_input};
    goto *aJump[scanfResult != 3];
  }

end_of_input:
  --pInstEnd;

  Inst *pCur = &aInst[0];
  int curRow = GRID_SIZE / 2;
  int curCol = GRID_SIZE / 2;
  aMap[curRow][curCol] = '#';

dig_trench_000:
  int aOff[] = {0, -1, 1};
  int offX = aOff[(pCur->dir == 'L') + 2 * (pCur->dir == 'R')];
  int offY = aOff[(pCur->dir == 'U') + 2 * (pCur->dir == 'D')];

  int dugSoFar = 0;
dig_trench_100:
  curRow += offY;
  curCol += offX;
  assert(!(curRow == 0 && curCol == 0)); // Need to make sure we have a starting point for the exterior flood fill
  assert(curRow >= 0);
  assert(curRow < GRID_SIZE);
  assert(curCol >= 0);
  assert(curCol < GRID_SIZE);
  aMap[curRow][curCol] = '#';
  {
    void *aJump[] = {&&dig_trench_100, &&dig_trench_200};
    goto *aJump[++dugSoFar == pCur->len];
  }

dig_trench_200:
  ++pCur;
  {
    void *aJump[] = {&&dig_trench_000, &&dig_trench_999};
    goto *aJump[pCur == pInstEnd];
  }

dig_trench_999:

#define FRONTIER_MAX_SIZE (GRID_SIZE * GRID_SIZE)
  Coord aFrontier[FRONTIER_MAX_SIZE + 1];
  int frontierSize = 0;
  aFrontier[frontierSize].x = 0;
  aFrontier[frontierSize].y = 0;
  aMap[0][0] = '@';
  ++frontierSize;

flood_fill_000:
  curRow = aFrontier[0].y;
  curCol = aFrontier[0].x;
  --frontierSize;
  memmove(aFrontier, aFrontier + 1, sizeof(Coord) * FRONTIER_MAX_SIZE);
  {
    void *aJump[] = {&&flood_fill_skip_up, &&flood_fill_add_up};
    goto *aJump[curRow > 0 && aMap[curRow - 1][curCol] == '.'];
  }

flood_fill_add_up:
  aFrontier[frontierSize].x = curCol;
  aFrontier[frontierSize].y = curRow - 1;
  aMap[curRow - 1][curCol] = '@';
  ++frontierSize;

flood_fill_skip_up:
{
  void *aJump[] = {&&flood_fill_skip_right, &&flood_fill_add_right};
  goto *aJump[curCol < (GRID_SIZE - 1) && aMap[curRow][curCol + 1] == '.'];
}

flood_fill_add_right:
  aFrontier[frontierSize].x = curCol + 1;
  aFrontier[frontierSize].y = curRow;
  aMap[curRow][curCol + 1] = '@';
  ++frontierSize;

flood_fill_skip_right:
{
  void *aJump[] = {&&flood_fill_skip_down, &&flood_fill_add_down};
  goto *aJump[curRow < (GRID_SIZE - 1) && aMap[curRow + 1][curCol] == '.'];
}

flood_fill_add_down:
  aFrontier[frontierSize].x = curCol;
  aFrontier[frontierSize].y = curRow + 1;
  aMap[curRow + 1][curCol] = '@';
  ++frontierSize;

flood_fill_skip_down:
{
  void *aJump[] = {&&flood_fill_skip_left, &&flood_fill_add_left};
  goto *aJump[curCol > 0 && aMap[curRow][curCol - 1] == '.'];
}

flood_fill_add_left:
  aFrontier[frontierSize].x = curCol - 1;
  aFrontier[frontierSize].y = curRow;
  aMap[curRow][curCol - 1] = '@';
  ++frontierSize;

flood_fill_skip_left:
  assert(frontierSize < FRONTIER_MAX_SIZE);
  {
    void *aJump[] = {&&flood_fill_000, &&flood_fill_999};
    goto *aJump[frontierSize == 0];
  }

flood_fill_999:

  int totalVolume = 0;
  char *pInterior = &aMap[0][0];
  char *pEndOfMap = &aMap[999][999] + 1;
count_trench_000:
  pInterior = memchr(pInterior, '#', pEndOfMap - pInterior);
  {
    void *aJump[] = {&&count_trench_100, &&count_trench_999};
    goto *aJump[pInterior == 0];
  }
count_trench_100:
  ++totalVolume;
  ++pInterior;
  goto count_trench_000;

count_trench_999:

  pInterior = &aMap[0][0];
count_inner_000:
  pInterior = memchr(pInterior, '.', pEndOfMap - pInterior);
  {
    void *aJump[] = {&&count_inner_100, &&count_inner_999};
    goto *aJump[pInterior == 0];
  }
count_inner_100:
  ++totalVolume;
  ++pInterior;
  goto count_inner_000;

count_inner_999:

  printf("%d\n", totalVolume);
}
