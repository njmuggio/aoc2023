#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char **pArgv)
{
  int fd = open(pArgv[1], O_RDONLY);

  int totalSum = 0;

  int firstDigit = -1;
  int lastDigit = -1;

read_line:
  char curChar = 0;
  ssize_t readStatus = read(fd, &curChar, 1);
  void *aEofJumpTable[] = {&&read_line_100, &&end_of_program};
  goto *aEofJumpTable[readStatus == 0];

read_line_100:
  void *aEolJumpTable[] = {&&read_line_200, &&add_to_sum};
  goto *aEolJumpTable[curChar == '\n'];

read_line_200:
  int isDigit = isdigit(curChar);
  // 0 == not a digit, 1 == first digit, 2 == after-first digit
  void *aIsDigitJumpTable[] = {&&read_line, &&first_digit, &&after_first_digit};
  goto *aIsDigitJumpTable[(isDigit != 0) + ((isDigit != 0) * (firstDigit >= 0))];

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
