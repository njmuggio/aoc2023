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

typedef struct IncCur_t
{
  long inc;
  long cur;
} IncCur;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  Node aNodes[26][26][26];
  memset(aNodes, 0, sizeof(aNodes));

  Node dummy = {0, 0, 0};

  int numActiveNodes = 0;
  Node *aCurNodes[6] = {&dummy, &dummy, &dummy, &dummy, &dummy, &dummy};
  IncCur aSteps[6];
  memset(aSteps, 0, sizeof(aSteps));

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
  char curDir = 0;

navigate_000:
{
  void *aJump[] = {
      &&step_count_1_init,
      &&step_count_2_init,
      &&step_count_3_init,
      &&step_count_4_init,
      &&step_count_5_init,
      &&step_count_6_init};
  goto *aJump[numActiveNodes - 1];
}

step_count_6_init:
  curDirIdx = 0;
step_count_6:
{
  void *aJump[] = {&&step_count_6_step, &&step_count_5_init};
  goto *aJump[aCurNodes[5]->isEndNode];
}
step_count_6_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[5].inc += 1;
  aCurNodes[5] = aCurNodes[5]->aDest[curDir == 'R'];
  goto step_count_6;

step_count_5_init:
  curDirIdx = 0;
step_count_5:
{
  void *aJump[] = {&&step_count_5_step, &&step_count_4_init};
  goto *aJump[aCurNodes[4]->isEndNode];
}
step_count_5_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[4].inc += 1;
  aCurNodes[4] = aCurNodes[4]->aDest[curDir == 'R'];
  goto step_count_5;

step_count_4_init:
  curDirIdx = 0;
step_count_4:
{
  void *aJump[] = {&&step_count_4_step, &&step_count_3_init};
  goto *aJump[aCurNodes[3]->isEndNode];
}
step_count_4_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[3].inc += 1;
  aCurNodes[3] = aCurNodes[3]->aDest[curDir == 'R'];
  goto step_count_4;

step_count_3_init:
  curDirIdx = 0;
step_count_3:
{
  void *aJump[] = {&&step_count_3_step, &&step_count_2_init};
  goto *aJump[aCurNodes[2]->isEndNode];
}
step_count_3_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[2].inc += 1;
  aCurNodes[2] = aCurNodes[2]->aDest[curDir == 'R'];
  goto step_count_3;

step_count_2_init:
  curDirIdx = 0;
step_count_2:
{
  void *aJump[] = {&&step_count_2_step, &&step_count_1_init};
  goto *aJump[aCurNodes[1]->isEndNode];
}
step_count_2_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[1].inc += 1;
  aCurNodes[1] = aCurNodes[1]->aDest[curDir == 'R'];
  goto step_count_2;

step_count_1_init:
  curDirIdx = 0;
step_count_1:
{
  void *aJump[] = {&&step_count_1_step, &&compute_lcm};
  goto *aJump[aCurNodes[0]->isEndNode];
}
step_count_1_step:
  curDir = pDirs[curDirIdx];
  curDirIdx = (curDirIdx + 1) % dirLen;

  aSteps[0].inc += 1;
  aCurNodes[0] = aCurNodes[0]->aDest[curDir == 'R'];
  goto step_count_1;

compute_lcm:
  IncCur *aMinOptions[2] = {&aSteps[0], 0};

  {
    void *aJump[] = {&&find_min_2, &&find_min_3, &&find_min_4, &&find_min_5, &&find_min_6};
    goto *aJump[numActiveNodes - 2];
  }

find_min_6:
  aMinOptions[1] = &aSteps[5];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];
find_min_5:
  aMinOptions[1] = &aSteps[4];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];
find_min_4:
  aMinOptions[1] = &aSteps[3];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];
find_min_3:
  aMinOptions[1] = &aSteps[2];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];
find_min_2:
  aMinOptions[1] = &aSteps[1];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];
find_min_1:
  aMinOptions[1] = &aSteps[0];
  aMinOptions[0] = aMinOptions[aMinOptions[1]->cur < aMinOptions[0]->cur];

  aMinOptions[0]->cur += aMinOptions[0]->inc;

  {
    void *aJump[] = {&&compute_lcm, &&found_lcm};
    int allMatch = (aSteps[0].cur == aSteps[1].cur) && (aSteps[0].cur == aSteps[2].cur || numActiveNodes < 3) && (aSteps[0].cur == aSteps[3].cur || numActiveNodes < 4) && (aSteps[0].cur == aSteps[4].cur || numActiveNodes < 5) && (aSteps[0].cur == aSteps[5].cur || numActiveNodes < 6);
    goto *aJump[allMatch];
  }

found_lcm:
  printf("%lu\n", aSteps[0].cur);
}
