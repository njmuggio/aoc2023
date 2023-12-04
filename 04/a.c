#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int totalScore = 0;
  int thisCardScore = 0;

  int aWinningNumbers[100];
  int winningCount = 0;

  int aCurrentNumbers[100];
  int currentCount = 0;

read_card_start:
  int cardNum;
  int scanfResult = fscanf(pInput, "Card %d: ", &cardNum);
  winningCount = 0;
  currentCount = 0;
  void *aEofJumpTable[] = {&&end_of_file_reached, &&read_winning_num};
  goto *aEofJumpTable[scanfResult == 1];

read_winning_num:
  scanfResult = fscanf(pInput, "%d", &aWinningNumbers[winningCount++]);
  void *aEndOfWinningNumsJumpTable[] = {&&end_of_winning_nums, &&read_winning_num};
  goto *aEndOfWinningNumsJumpTable[scanfResult];

end_of_winning_nums:
  winningCount -= 1;
  fscanf(pInput, "|");

read_current_num:
  scanfResult = fscanf(pInput, "%d", &aCurrentNumbers[currentCount++]);
  void *aEndOfCurrentNumsJumpTable[] = {&&end_of_current_nums, &&read_current_num};
  goto *aEndOfCurrentNumsJumpTable[scanfResult == 1];

end_of_current_nums:
  // currentCount -= 1;
  currentCount += (scanfResult - 1);
  // size_t len = 1;
  // qsort_r(aWinningNumbers, winningCount, sizeof(int), memcmp, (void *)len);
  // qsort_r(aCurrentNumbers, currentCount, sizeof(int), memcmp, (void *)len);

  int winIdx = 0;
  int curIdx = 0;
  thisCardScore = 0;

check_for_winning_num_start:
  thisCardScore += aCurrentNumbers[curIdx] == aWinningNumbers[winIdx];
  curIdx += 1;
  winIdx += curIdx == currentCount;
  curIdx %= currentCount;

  void *aEndOfWinCheckJumpTable[] = {&&check_for_winning_num_start, &&end_of_win_num_check};
  goto *aEndOfWinCheckJumpTable[winIdx == winningCount];

end_of_win_num_check:
  totalScore += (1 << thisCardScore) >> 1;
  goto read_card_start;

end_of_file_reached:
  printf("%d\n", totalScore);

  return 0;
}
