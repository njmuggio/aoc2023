#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

enum Type
{
  HighCard = 0,
  OnePair = 1,
  TwoPair = 1 << 1,
  ThreeKind = 1 << 2,
  FullHouse = 1 << 3,
  FourKind = 1 << 4,
  FiveKind = 1 << 5
};

typedef struct Score_t
{
  unsigned char type;
  unsigned char aHand[5];
  unsigned short bid;
} Score;

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int aFirstTranslation[] = {['2'] = 1, ['3'] = 2, ['4'] = 3, ['5'] = 4, ['6'] = 5, ['7'] = 6, ['8'] = 7, ['9'] = 8, ['T'] = 9, ['J'] = 0, ['Q'] = 11, ['K'] = 12, ['A'] = 13};

  char aJokerTranslate[] = {['2'] = '2', ['3'] = '3', ['4'] = '4', ['5'] = '5', ['6'] = '6', ['7'] = '7', ['8'] = '8', ['9'] = '9', ['T'] = 'T', ['J'] = 'Z', ['Q'] = 'Q', ['K'] = 'K', ['A'] = 'A'};

  int handCount = 0;
  char aHands[1000][6];
  char aSorted[1000][6];
  int aJokers[1000];
  int aBids[1000];
  int aType[1000];
  int aRank[1000];
  Score aScore[1000];
  memset(aHands, 0, sizeof(aHands));
  memset(aSorted, 0, sizeof(aSorted));
  memset(aJokers, 0, sizeof(aJokers));
  memset(aBids, 0, sizeof(aBids));
  memset(aType, HighCard, sizeof(aType));
  memset(aRank, 0, sizeof(aRank));
  memset(aScore, 0, sizeof(aScore));

read_all_hands_000:
  int scanfResult = fscanf(pInput, "%5s %d", aHands[handCount], &aBids[handCount]);
  {
    void *aJump[] = {&&read_all_hands_100, &&read_all_hands_done};
    goto *aJump[scanfResult != 2];
  }
read_all_hands_100:
  aSorted[handCount][0] = aJokerTranslate[aHands[handCount][0]];
  aSorted[handCount][1] = aJokerTranslate[aHands[handCount][1]];
  aSorted[handCount][2] = aJokerTranslate[aHands[handCount][2]];
  aSorted[handCount][3] = aJokerTranslate[aHands[handCount][3]];
  aSorted[handCount][4] = aJokerTranslate[aHands[handCount][4]];
  qsort_r(aSorted[handCount], 5, 1, memcmp, (void *)1ul);
  aJokers[handCount] = (aHands[handCount][0] == 'J') + (aHands[handCount][1] == 'J') + (aHands[handCount][2] == 'J') + (aHands[handCount][3] == 'J') + (aHands[handCount][4] == 'J');
  ++handCount;
  goto read_all_hands_000;

read_all_hands_done:

  int curHand = 0;
  char *pSorted = 0;
identify_hand_type_000:
  // all hand typ9es identified?
  {
    void *aJump[] = {&&identify_hand_type_100, &&identify_hand_type_end};
    goto *aJump[curHand == handCount];
  }
identify_hand_type_100:
  pSorted = aSorted[curHand];
  int jokers = aJokers[curHand];

  // clang-format off
  aType[curHand] = FiveKind * (
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3] && pSorted[3] == pSorted[4]) || // XXXXX
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3] && jokers == 1) ||              // XXXXJ
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && jokers == 2) ||                                          // XXXJJ
    (pSorted[0] == pSorted[1] && jokers == 3) ||                                                                      // XXJJJ
    (jokers >= 4)                                                                                                     // XJJJJ, JJJJJ
  );
  {
    void* aJump[] = {&&check_four_kind, &&found_hand_type};
    goto *aJump[aType[curHand] != 0];
  }

check_four_kind:
  aType[curHand] = FourKind * (
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3]) || // XXXXA
    (pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3] && pSorted[3] == pSorted[4]) || // AXXXX
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && jokers == 1) ||              // XXXAJ
    (pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3] && jokers == 1) ||              // AXXXJ
    (pSorted[0] == pSorted[1] && jokers == 2) ||                                          // XXAJJ
    (pSorted[1] == pSorted[2] && jokers == 2) ||                                          // AXXJJ
    (jokers == 3)                                                                         // ABJJJ
  );
  {
    void* aJump[] = {&&check_full_house, &&found_hand_type};
    goto *aJump[aType[curHand] != 0];
  }

check_full_house:
  aType[curHand] = FullHouse * (
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2] && pSorted[3] == pSorted[4]) || // XXXYY
    (pSorted[0] == pSorted[1] && pSorted[2] == pSorted[3] && pSorted[3] == pSorted[4]) || // XXYYY
    (pSorted[0] == pSorted[1] && pSorted[2] == pSorted[3] && jokers == 1)                 // XXYYJ
  );
  {
    void* aJump[] = {&&check_three_kind, &&found_hand_type};
    goto *aJump[aType[curHand] != 0];
  }

check_three_kind:
  aType[curHand] = ThreeKind * (
    (pSorted[0] == pSorted[1] && pSorted[1] == pSorted[2]) || // XXXAB
    (pSorted[1] == pSorted[2] && pSorted[2] == pSorted[3]) || // AXXXB
    (pSorted[2] == pSorted[3] && pSorted[3] == pSorted[4]) || // ABXXX
    (pSorted[0] == pSorted[1] && jokers == 1) ||              // XXABJ
    (pSorted[1] == pSorted[2] && jokers == 1) ||              // AXXBJ
    (pSorted[2] == pSorted[3] && jokers == 1) ||              // ABXXJ
    (jokers == 2)                                             // ABCJJ
  );
  {
    void* aJump[] = {&&check_two_pair, &&found_hand_type};
    goto *aJump[aType[curHand] != 0];
  }

check_two_pair:
  aType[curHand] = TwoPair * (
    (pSorted[0] == pSorted[1] && pSorted[2] == pSorted[3]) || // XXYYA
    (pSorted[0] == pSorted[1] && pSorted[3] == pSorted[4]) || // XXAYY
    (pSorted[1] == pSorted[2] && pSorted[3] == pSorted[4])    // AXXYY
  );
  {
    void* aJump[] = {&&check_one_pair, &&found_hand_type};
    goto *aJump[aType[curHand] != 0];
  }

check_one_pair:
  aType[curHand] = OnePair * (
    (pSorted[0] == pSorted[1]) || // XXABC
    (pSorted[1] == pSorted[2]) || // AXXBC
    (pSorted[2] == pSorted[3]) || // ABXXC
    (pSorted[3] == pSorted[4]) || // ABCXX
    (jokers == 1)                 // ABCDJ
  );
  // clang-format on

found_hand_type:

  aScore[curHand].bid = aBids[curHand];
  aScore[curHand].aHand[0] = aFirstTranslation[aHands[curHand][0]];
  aScore[curHand].aHand[1] = aFirstTranslation[aHands[curHand][1]];
  aScore[curHand].aHand[2] = aFirstTranslation[aHands[curHand][2]];
  aScore[curHand].aHand[3] = aFirstTranslation[aHands[curHand][3]];
  aScore[curHand].aHand[4] = aFirstTranslation[aHands[curHand][4]];
  aScore[curHand].type = aType[curHand];

  // int lz = __builtin_clz(aType[curHand]);
  // aScore[curHand].type = (aType[curHand] >> (31 - lz)) << (31 - lz);

  ++curHand;
  goto identify_hand_type_000;

identify_hand_type_end:

  qsort_r(aScore, handCount, sizeof(Score), memcmp, (void *)sizeof(Score));

  int curRank = handCount;
  curHand = handCount - 1;
  int totalWinnings = 0;
sum_total_winnings:
  printf("%d\t%hhu\t%hhu\t%hhu\t%hhu\t%hhu\t%hhu\t%hu\n", curRank, aScore[curHand].type, aScore[curHand].aHand[0], aScore[curHand].aHand[1], aScore[curHand].aHand[2], aScore[curHand].aHand[3], aScore[curHand].aHand[4], aScore[curHand].bid);
  totalWinnings += curRank-- * aScore[curHand--].bid;
  {
    void *aJump[] = {&&sum_total_winnings, &&print_result};
    goto *aJump[curHand < 0];
  }

print_result:
  printf("%d\n", totalWinnings);

  return 0;
}
