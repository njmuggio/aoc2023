#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const char *one = "one";
const char *two = "two";
const char *three = "three";
const char *four = "four";
const char *five = "five";
const char *six = "six";
const char *seven = "seven";
const char *eight = "eight";
const char *nine = "nine";

const char *aWordNums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
int aWordLens[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

char aHistBuf[5] = {0, 0, 0, 0, 0};

int main(int argc, char **pArgv)
{
  int fd = open(pArgv[1], O_RDONLY);

  int totalSum = 0;

  int firstDigit = -1;
  int lastDigit = -1;

  // int idxInLine = -1;

read_line:
  char curChar = 0;
  ssize_t readStatus = read(fd, &curChar, 1);
  // idxInLine++;
  memmove(aHistBuf, aHistBuf + 1, 4);
  aHistBuf[4] = curChar;
  void *aEofJumpTable[] = {&&read_line_100, &&end_of_program};
  goto *aEofJumpTable[readStatus == 0];

read_line_100:
  void *aEolJumpTable[] = {&&read_line_200, &&add_to_sum};
  goto *aEolJumpTable[curChar == '\n'];

read_line_200:
  int isDigit = isdigit(curChar);
  // 0 == not a digit, 1 == first digit, 2 == after-first digit
  void *aIsDigitJumpTable[] = {&&read_line_300, &&first_digit, &&after_first_digit};
  goto *aIsDigitJumpTable[(isDigit != 0) + ((isDigit != 0) * (firstDigit >= 0))];

read_line_300:
  // void *aSkipWordJumpTable[] = {&&test_one, &&skip_one};
  // goto *aSkipWordJumpTable[idxInLine < aWordLens[0]];

test_one:
  curChar = '1';
  int match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[0], aWordNums[0], aWordLens[0]);
  void *aMatchJumpTable[] = {&&skip_one, &&first_digit, &&after_first_digit};
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_one:
  //   aSkipWordJumpTable[0] = &&test_two;
  //   aSkipWordJumpTable[1] = &&skip_two;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[1]];

test_two:
  curChar = '2';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[1], aWordNums[1], aWordLens[1]);
  aMatchJumpTable[0] = &&skip_two;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_two:
  //   aSkipWordJumpTable[0] = &&test_three;
  //   aSkipWordJumpTable[1] = &&skip_three;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[2]];

test_three:
  curChar = '3';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[2], aWordNums[2], aWordLens[2]);
  aMatchJumpTable[0] = &&skip_three;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_three:
  //   aSkipWordJumpTable[0] = &&test_four;
  //   aSkipWordJumpTable[1] = &&skip_four;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[3]];

test_four:
  curChar = '4';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[3], aWordNums[3], aWordLens[3]);
  aMatchJumpTable[0] = &&skip_four;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_four:
  //   aSkipWordJumpTable[0] = &&test_five;
  //   aSkipWordJumpTable[1] = &&skip_five;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[4]];

test_five:
  curChar = '5';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[4], aWordNums[4], aWordLens[4]);
  aMatchJumpTable[0] = &&skip_five;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_five:
  //   aSkipWordJumpTable[0] = &&test_six;
  //   aSkipWordJumpTable[1] = &&skip_six;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[5]];

test_six:
  curChar = '6';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[5], aWordNums[5], aWordLens[5]);
  aMatchJumpTable[0] = &&skip_six;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_six:
  //   aSkipWordJumpTable[0] = &&test_seven;
  //   aSkipWordJumpTable[1] = &&skip_seven;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[6]];

test_seven:
  curChar = '7';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[6], aWordNums[6], aWordLens[6]);
  aMatchJumpTable[0] = &&skip_seven;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_seven:
  //   aSkipWordJumpTable[0] = &&test_eight;
  //   aSkipWordJumpTable[1] = &&skip_eight;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[7]];

test_eight:
  curChar = '8';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[7], aWordNums[7], aWordLens[7]);
  aMatchJumpTable[0] = &&skip_eight;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_eight:
  //   aSkipWordJumpTable[0] = &&test_nine;
  //   aSkipWordJumpTable[1] = &&skip_nine;
  //   goto *aSkipWordJumpTable[idxInLine < aWordLens[8]];

test_nine:
  curChar = '9';
  match = strncmp(aHistBuf + sizeof(aHistBuf) - aWordLens[8], aWordNums[8], aWordLens[8]);
  aMatchJumpTable[0] = &&skip_nine;
  goto *aMatchJumpTable[(match == 0) + ((match == 0) * (firstDigit >= 0))];

skip_nine:
  goto read_line;

first_digit:
  firstDigit = curChar - '0';
after_first_digit:
  lastDigit = curChar - '0';
  goto read_line;

add_to_sum:
  totalSum += firstDigit * 10 + lastDigit;
  firstDigit = lastDigit = -1;
  goto read_line;

end_of_program:
  printf("%d\n", totalSum);
}
