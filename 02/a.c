#include <stdio.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int totalIdSum = 0;

  int gameId = 0;
  int colorCount = 0;

read_game_0000:
  int scanfResult = fscanf(pInput, "Game %d: ", &gameId);
  int isValidGame = 1;
  void *aEofJumpTable[] = {&&read_next_color, &&end_of_file};
  goto *aEofJumpTable[scanfResult == EOF];

read_next_color:
  char aColor[10] = {0};
  int count = 0;
  char nextChar = 0;
  int isEndOfHand = 0;

  scanfResult = fscanf(pInput, "%d %s%c", &count, aColor, &nextChar);

  void *aColorJumpTable[] = {&&is_red, &&is_green, &&is_blue};
  goto *aColorJumpTable[(aColor[0] == 'g') + (2 * (aColor[0] == 'b'))];

is_red:
  isValidGame &= (count <= 12);
  isEndOfHand = (aColor[3] == ';') || nextChar == '\n';
  goto end_of_color;

is_green:
  isValidGame &= (count <= 13);
  isEndOfHand = (aColor[5] == ';') || nextChar == '\n';
  goto end_of_color;

is_blue:
  isValidGame &= (count <= 14);
  isEndOfHand = (aColor[4] == ';') || nextChar == '\n';

end_of_color:
  void *aEndOfHandJumpTable[] = {&&read_next_color, &&end_of_hand};
  goto *aEndOfHandJumpTable[isEndOfHand];

end_of_hand:
  void *aEndOfGameJumpTable[] = {&&read_next_color, &&check_valid_game};
  goto *aEndOfGameJumpTable[nextChar == '\n'];

check_valid_game:
  void *aIsValidGameJumpTable[] = {&&read_game_0000, &&valid_game};
  goto *aIsValidGameJumpTable[isValidGame];

valid_game:
  totalIdSum += gameId;
  goto read_game_0000;

end_of_file:
  printf("%d\n", totalIdSum);
}
