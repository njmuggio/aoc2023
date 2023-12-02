#include <stdio.h>
#include <limits.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int totalPowerSum = 0;

  int gameId = 0;
  int colorCount = 0;

read_game_0000:
  int scanfResult = fscanf(pInput, "Game %d: ", &gameId);

  int maxRed = INT_MIN;
  int maxGreen = INT_MIN;
  int maxBlue = INT_MIN;

  void *aEofJumpTable[] = {&&read_next_color, &&end_of_file};
  goto *aEofJumpTable[scanfResult == EOF];

read_next_color:
  char aColor[10] = {0};
  char nextChar = 0;
  int isEndOfHand = 0;

  int aMaxBuf[2];

  scanfResult = fscanf(pInput, "%d %s%c", &aMaxBuf[1], aColor, &nextChar);

  void *aColorJumpTable[] = {&&is_red, &&is_green, &&is_blue};
  goto *aColorJumpTable[(aColor[0] == 'g') + (2 * (aColor[0] == 'b'))];

is_red:
  aMaxBuf[0] = maxRed;
  maxRed = aMaxBuf[aMaxBuf[1] > aMaxBuf[0]];
  isEndOfHand = (aColor[3] == ';') || nextChar == '\n';
  goto end_of_color;

is_green:
  aMaxBuf[0] = maxGreen;
  maxGreen = aMaxBuf[aMaxBuf[1] > aMaxBuf[0]];
  isEndOfHand = (aColor[5] == ';') || nextChar == '\n';
  goto end_of_color;

is_blue:
  aMaxBuf[0] = maxBlue;
  maxBlue = aMaxBuf[aMaxBuf[1] > aMaxBuf[0]];
  isEndOfHand = (aColor[4] == ';') || nextChar == '\n';

end_of_color:
  void *aEndOfGameJumpTable[] = {&&read_next_color, &&end_of_game};
  goto *aEndOfGameJumpTable[nextChar == '\n'];

end_of_game:
  int gamePower = maxRed * maxGreen * maxBlue;
  totalPowerSum += gamePower;
  goto read_game_0000;

end_of_file:
  printf("%d\n", totalPowerSum);
}
