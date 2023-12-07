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

  int aFirstTranslation[] = {['2'] = 1, ['3'] = 2, ['4'] = 3, ['5'] = 4, ['6'] = 5, ['7'] = 6, ['8'] = 7, ['9'] = 8, ['T'] = 9, ['J'] = 10, ['Q'] = 11, ['K'] = 12, ['A'] = 13};

  int handCount = 0;
  char aHands[1000][6];
  char aSorted[1000][6];
  int aBids[1000];
  // int aFirst[1000];
  int aType[1000];
  int aRank[1000];
  Score aScore[1000];
  memset(aHands, 0, sizeof(aHands));
  memset(aSorted, 0, sizeof(aSorted));
  memset(aBids, 0, sizeof(aBids));
  // memset(aFirst, 0, sizeof(aFirst));
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
  memcpy(aSorted[handCount], aHands[handCount], 5);
  qsort_r(aSorted[handCount], 5, 1, memcmp, (void *)1ul);
  // aFirst[handCount] = aFirstTranslation[aHands[handCount][0]];
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
  // clang-format off
  aType[curHand] |= OnePair * (
    (pSorted[0] == pSorted[1]) || // XXABC
    (pSorted[1] == pSorted[2]) || // AXXBC
    (pSorted[2] == pSorted[3]) || // ABXXC
    (pSorted[3] == pSorted[4])    // ABCXX
  );

  aType[curHand] |= TwoPair * (
    (
      (pSorted[0] == pSorted[1]) && (
        (pSorted[2] == pSorted[3]) || // XXYYA
        (pSorted[3] == pSorted[4]))   // XXAYY
    ) || (
      (pSorted[1] == pSorted[2]) && (
        (pSorted[3] == pSorted[4]) // AXXYY
      )
    )
  );

  aType[curHand] |= ThreeKind * (
    ((pSorted[0] == pSorted[1]) && (pSorted[1] == pSorted[2])) || // XXXAB
    ((pSorted[1] == pSorted[2]) && (pSorted[2] == pSorted[3])) || // AXXXB
    ((pSorted[2] == pSorted[3]) && (pSorted[3] == pSorted[4]))    // ABXXX
  );

  aType[curHand] |= FullHouse * (
    ((pSorted[0] == pSorted[1]) && (pSorted[1] == pSorted[2]) && (pSorted[3] == pSorted[4])) || // XXXYY
    ((pSorted[0] == pSorted[1]) && (pSorted[2] == pSorted[3]) && (pSorted[3] == pSorted[4]))    // XXYYY
  );

  aType[curHand] |= FourKind * (
    ((pSorted[0] == pSorted[1]) && (pSorted[1] == pSorted[2]) && (pSorted[2] == pSorted[3])) || // XXXXA
    ((pSorted[1] == pSorted[2]) && (pSorted[2] == pSorted[3]) && (pSorted[3] == pSorted[4]))    // AXXXX
  );

  aType[curHand] |= FiveKind * (
    ((pSorted[0] == pSorted[1]) && (pSorted[1] == pSorted[2]) && (pSorted[2] == pSorted[3]) && (pSorted[3] == pSorted[4])) // XXXXX
  );
  // clang-format on

  // aScore[curHand] = (1 << (__builtin_clz(aType[curHand]) + 24)) + (aFirst[curHand] << 16) + aBids[curHand];
  // aScore[curHand] = (aBids[curHand] << 16) + (aFirst[curHand] << 8) + (1 << ((sizeof(int) * CHAR_BIT) - __builtin_clz(aType[curHand]) - 1));
  aScore[curHand].bid = aBids[curHand];
  aScore[curHand].aHand[0] = aFirstTranslation[aHands[curHand][0]];
  aScore[curHand].aHand[1] = aFirstTranslation[aHands[curHand][1]];
  aScore[curHand].aHand[2] = aFirstTranslation[aHands[curHand][2]];
  aScore[curHand].aHand[3] = aFirstTranslation[aHands[curHand][3]];
  aScore[curHand].aHand[4] = aFirstTranslation[aHands[curHand][4]];

  int lz = __builtin_clz(aType[curHand]);
  // aScore[curHand].type = 1 << ((sizeof(int) * CHAR_BIT) - __builtin_clz(aType[curHand]) - 1);
  aScore[curHand].type = (aType[curHand] >> (31 - lz)) << (31 - lz);

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
