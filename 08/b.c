#include <stdio.h>
#include <string.h>

typedef struct Node_t
{
  union
  {
    struct
    {
      struct Node_t *pLeft;
      struct Node_t *pRight;
    };
    struct Node_t *aDest[2];
  };

  int isEndNode;
} Node;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  Node aNodes[26][26][26];
  memset(aNodes, 0, sizeof(aNodes));

  Node dummy = {0, 0, 0};

  int numActiveNodes = 0;
  Node *aCurNodes[6] = {&dummy, &dummy, &dummy, &dummy, &dummy, &dummy};

  Node *pStartNode = &aNodes[0][0][0];
  Node *pEndNode = &aNodes[25][25][25];

  char *pDirs = 0;
  size_t bufLen = 0;
  ssize_t dirLen = getline(&pDirs, &bufLen, pInput);
  --dirLen;
  pDirs[dirLen] = 0;

read_instructions_000:
  char aNodeName[4];
  char aLeftName[4];
  char aRightName[4];

  int scanfResult = fscanf(pInput, "%3s = (%3s, %3s) ", aNodeName, aLeftName, aRightName);
  {
    void *aJump[] = {&&read_instructions_100, &&read_instructions_end};
    goto *aJump[scanfResult != 3];
  }

read_instructions_100:
  Node *pCurNode = &aNodes[aNodeName[0] - 'A'][aNodeName[1] - 'A'][aNodeName[2] - 'A'];
  pCurNode->pLeft = &aNodes[aLeftName[0] - 'A'][aLeftName[1] - 'A'][aLeftName[2] - 'A'];
  pCurNode->pRight = &aNodes[aRightName[0] - 'A'][aRightName[1] - 'A'][aRightName[2] - 'A'];
  pCurNode->isEndNode = aNodeName[2] == 'Z';

  {
    void *aJump[] = {&&read_instructions_200, &&read_instructions_000};
    goto *aJump[aNodeName[2] != 'A'];
  }
read_instructions_200:
  aCurNodes[numActiveNodes++] = pCurNode;
  goto read_instructions_000;

read_instructions_end:

  int curDirIdx = 0;
  unsigned long totalSteps = 0;

navigate_000:
  // All nodes at terminator?
  {
    int numNodesAtFinal = aCurNodes[0]->isEndNode + aCurNodes[1]->isEndNode + aCurNodes[2]->isEndNode + aCurNodes[3]->isEndNode + aCurNodes[4]->isEndNode + aCurNodes[5]->isEndNode;
    if (numNodesAtFinal > 3)
      printf("Step %lu, num at final %d\n", totalSteps, numNodesAtFinal);
    void *aJump[] = {&&navigate_100, &&found_zzz};
    goto *aJump[numNodesAtFinal == numActiveNodes];
  }
navigate_100:
  ++totalSteps;
  char curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;
  {
    void *aJump[] = {&&navigate_200_1,
                     &&navigate_200_2,
                     &&navigate_200_3,
                     &&navigate_200_4,
                     &&navigate_200_5,
                     &&navigate_200_6};
    goto *aJump[numActiveNodes - 1];
  }
navigate_200_6:
  aCurNodes[5] = aCurNodes[5]->aDest[curDir == 'R'];
navigate_200_5:
  aCurNodes[4] = aCurNodes[4]->aDest[curDir == 'R'];
navigate_200_4:
  aCurNodes[3] = aCurNodes[3]->aDest[curDir == 'R'];
navigate_200_3:
  aCurNodes[2] = aCurNodes[2]->aDest[curDir == 'R'];
navigate_200_2:
  aCurNodes[1] = aCurNodes[1]->aDest[curDir == 'R'];
navigate_200_1:
  aCurNodes[0] = aCurNodes[0]->aDest[curDir == 'R'];

  goto navigate_000;

found_zzz:
  printf("%lu\n", totalSteps);
}
