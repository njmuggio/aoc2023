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
  char c;
} Node;

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

  Node *pFarthest = pStart;

advance_two_nodes:
  pCur->pNext = pCur->aNeighbors[pCur->pNeighbor1->visited];
  pCur->pNext->distFromStart = pCur->distFromStart + 1;
  pCur = pCur->pNext;
  pCur->visited = 1;

  pCur->pNext = pCur->aNeighbors[pCur->pNeighbor1->visited];
  pCur->pNext->distFromStart = pCur->distFromStart + 1;
  pCur = pCur->pNext;
  pCur->visited = 1;

  pFarthest = pFarthest->pNext;

  {
    void *aJump[] = {&&advance_two_nodes, &&found_pipe_loop};
    goto *aJump[pCur->pNeighbor1->visited * pCur->pNeighbor2->visited];
  }

found_pipe_loop:
  printf("%d\n", pFarthest->distFromStart);
}
