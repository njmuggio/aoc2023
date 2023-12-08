#include <stdio.h>
#include <string.h>

typedef struct Node_t
{
  struct Node_t *pLeft;
  struct Node_t *pRight;
} Node;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  Node aNodes[26][26][26];
  memset(aNodes, 0, sizeof(aNodes));

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
  goto read_instructions_000;

read_instructions_end:
  pCurNode = pStartNode;

  int curDirIdx = 0;
  int totalSteps = 0;

navigate_000:
{
  void *aJump[] = {&&navigate_100, &&found_zzz};
  goto *aJump[pCurNode == pEndNode];
}
navigate_100:
  ++totalSteps;
  char curDir = pDirs[curDirIdx++ % dirLen];
  Node *pNodeOptions[] = {pCurNode->pLeft, pCurNode->pRight};
  pCurNode = pNodeOptions[curDir == 'R'];
  goto navigate_000;

found_zzz:
  printf("%d\n", totalSteps);
}
