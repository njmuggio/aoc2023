#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int thisCardScore = 0;

  int aWinningNumbers[100];
  int winningCount = 0;

  int aCurrentNumbers[100];
  int currentCount = 0;

  int aCardRepeat[200] = {};

read_card_start:
  int curCard;
  int scanfResult = fscanf(pInput, "Card %d: ", &curCard);
  winningCount = 0;
  currentCount = 0;
  void *aEofJumpTable[] = {&&end_of_file_reached, &&saw_card_start};
  goto *aEofJumpTable[scanfResult == 1];

saw_card_start:
  aCardRepeat[curCard - 1] += 1;

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
  currentCount += (scanfResult - 1);

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
  int thisCardIdx = curCard - 1;
add_won_cards_lp_start:
  void *aEndOfCardAdderJumpTable[] = {&&add_won_cards_lp_mid, &&end_of_card_adder};
  goto *aEndOfCardAdderJumpTable[thisCardScore == 0];
add_won_cards_lp_mid:
  aCardRepeat[thisCardIdx + thisCardScore] += aCardRepeat[thisCardIdx];
  thisCardScore -= 1;
  goto add_won_cards_lp_start;

end_of_card_adder:
  goto read_card_start;

end_of_file_reached:
  int totalCardCount = 0;
card_sum_lp:
  void *aEndOfCardSumLpJumpTable[] = {&&card_sum_lp_mid, &&end};
  goto *aEndOfCardSumLpJumpTable[curCard == 0];
card_sum_lp_mid:
  totalCardCount += aCardRepeat[--curCard];
  goto card_sum_lp;

end:
  printf("%d\n", totalCardCount);

  return 0;
}
