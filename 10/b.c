#include <stdio.h>
#include <string.h>

typedef struct Node_t
{
  union
  {
    struct
    {
      struct Node_t *pNeighbor1;
      struct Node_t *pNeighbor2;
    };
    struct Node_t *aNeighbors[2];
  };

  struct Node_t *pNext;

  int distFromStart;
  int visited;

  int row;
  int col;

  char c;
} Node;

typedef struct Coord_t
{
  int row;
  int col;
} Coord;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  Node aNodes[140][140];
  memset(aNodes, 0, sizeof(aNodes));

  Node *pStart = 0;

  int gridSize = 0;

  int curRow = 0;

read_next_char:
  char c = getc(pInput);
  {
    void *aJump[] = {&&populate_next_char, &&advance_to_next_line, &&end_of_input};
    goto *aJump[(c == '\n') + (2 * (c == EOF))];
  }

populate_next_char:
  aNodes[curRow][gridSize].c = c;

  // aNeighborOffsets[thisShape] for neighbor1, aNeighborOffsets[thisShape + 1] for neighbor2
  int aNeighborOffsets[] = {
      ['|'] = -140,
      140,
      ['-'] = -1,
      1,
      ['L'] = -140,
      1,
      ['J'] = -1,
      -140,
      ['7'] = -1,
      140,
      ['F'] = 1,
      140};

  aNodes[curRow][gridSize].pNeighbor1 = &aNodes[curRow][gridSize] + aNeighborOffsets[c];
  aNodes[curRow][gridSize].pNeighbor2 = &aNodes[curRow][gridSize] + aNeighborOffsets[c + 1];
  aNodes[curRow][gridSize].row = curRow;
  aNodes[curRow][gridSize].col = gridSize;
  gridSize++;

  {
    void *aJump[] = {&&read_next_char, &&found_start_node};
    goto *aJump[c == 'S'];
  }

found_start_node:
  pStart = &aNodes[curRow][gridSize - 1];
  goto read_next_char;

advance_to_next_line:
  gridSize = 0;
  curRow++;
  goto read_next_char;

end_of_input:
  gridSize = curRow;

find_start_pipe_type:
  char rightPipe = (pStart + 1)->c;
  char upPipe = (pStart - 140)->c;
  char downPipe = (pStart + 140)->c;

  char aStartOptions[] = {'L', 'F'};
  pStart->c = aStartOptions[downPipe == '|' || downPipe == 'J'];

  pStart->pNeighbor1 = pStart + aNeighborOffsets[pStart->c];
  pStart->pNeighbor2 = pStart + aNeighborOffsets[pStart->c + 1];

  Node *pCur = pStart;
  pCur->visited = 1;

  char aUL[] = {['|'] = 'X', ['-'] = 'X', ['L'] = 'X', ['J'] = 'X', ['7'] = 'X', ['F'] = 'X'};
  char aUR[] = {['|'] = ' ', ['-'] = 'X', ['L'] = 'X', ['J'] = ' ', ['7'] = ' ', ['F'] = 'X'};
  char aDL[] = {['|'] = 'X', ['-'] = ' ', ['L'] = ' ', ['J'] = ' ', ['7'] = 'X', ['F'] = 'X'};
  char aDR[] = {['|'] = ' ', ['-'] = ' ', ['L'] = ' ', ['J'] = ' ', ['7'] = ' ', ['F'] = ' '};

  char aInflated[280][280];
  memset(aInflated, ' ', sizeof(aInflated));

  aInflated[pStart->row * 2][pStart->col * 2] = aUL[pStart->c];
  aInflated[pStart->row * 2][pStart->col * 2 + 1] = aUR[pStart->c];
  aInflated[pStart->row * 2 + 1][pStart->col * 2] = aDL[pStart->c];
  aInflated[pStart->row * 2 + 1][pStart->col * 2 + 1] = aDR[pStart->c];

advance_node:
  pCur->pNext = pCur->aNeighbors[pCur->pNeighbor1->visited];
  pCur->pNext->distFromStart = pCur->distFromStart + 1;
  pCur = pCur->pNext;
  pCur->visited = 1;
  aInflated[pCur->row * 2][pCur->col * 2] = aUL[pCur->c];
  aInflated[pCur->row * 2][pCur->col * 2 + 1] = aUR[pCur->c];
  aInflated[pCur->row * 2 + 1][pCur->col * 2] = aDL[pCur->c];
  aInflated[pCur->row * 2 + 1][pCur->col * 2 + 1] = aDR[pCur->c];

  {
    void *aJump[] = {&&advance_node, &&found_pipe_loop};
    goto *aJump[pCur->pNeighbor1->visited * pCur->pNeighbor2->visited];
  }

found_pipe_loop:
  Coord aFrontier[280 * 280];
  int frontierSize = 0;
  memset(aFrontier, 0, sizeof(aFrontier));
  aFrontier[frontierSize].row = 0;
  aFrontier[frontierSize++].col = 0;

flood_fill_000:
  // Frontier empty?
  {
    void *aJump[] = {&&flood_fill_100, &&flood_fill_end};
    goto *aJump[frontierSize == 0];
  }

flood_fill_100:
  --frontierSize;
  int row = aFrontier[frontierSize].row;
  int col = aFrontier[frontierSize].col;
  aInflated[row][col] = 'X';
  {
    void *aJump[] = {&&skip_u, &&add_u};
    goto *aJump[row > 0 && aInflated[row - 1][col] != 'X'];
  }

add_u:
  aFrontier[frontierSize].row = row - 1;
  aFrontier[frontierSize++].col = col;
skip_u:
{
  void *aJump[] = {&&skip_l, &&add_l};
  goto *aJump[col > 0 && aInflated[row][col - 1] != 'X'];
}

add_l:
  aFrontier[frontierSize].row = row;
  aFrontier[frontierSize++].col = col - 1;
skip_l:
{
  void *aJump[] = {&&skip_r, &&add_r};
  goto *aJump[col < (gridSize * 2 - 1) && aInflated[row][col + 1] != 'X'];
}

add_r:
  aFrontier[frontierSize].row = row;
  aFrontier[frontierSize++].col = col + 1;
skip_r:
{
  void *aJump[] = {&&skip_d, &&add_d};
  goto *aJump[row < (gridSize * 2 - 1) && aInflated[row + 1][col] != 'X'];
}

add_d:
  aFrontier[frontierSize].row = row + 1;
  aFrontier[frontierSize++].col = col;

skip_d:
  goto flood_fill_000;

flood_fill_end:
  row = 0;
  col = 0;
  int totalInternalCells = 0;
scan_row:
{
  void *aJump[] = {&&check_cell, &&next_row};
  goto *aJump[col == gridSize];
}
check_cell:
  totalInternalCells += (aInflated[row * 2][col * 2] == ' ') && (aInflated[row * 2][col * 2 + 1] == ' ') && (aInflated[row * 2 + 1][col * 2] == ' ') && (aInflated[row * 2 + 1][col * 2 + 1] == ' ');
  ++col;
  goto scan_row;

next_row:
  col = 0;
  ++row;
  {
    void *aJump[] = {&&scan_row, &&all_rows_scanned};
    goto *aJump[row == gridSize];
  }

all_rows_scanned:
  printf("%d\n", totalInternalCells);
}
