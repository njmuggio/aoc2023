#include <stdio.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  unsigned total = 0;
  unsigned hash = 0;

read_next:
  unsigned char nextChar = getc(pInput);
  {
    void *aJump[] = {&&hash_step, &&add_hash, &&eol};
    goto *aJump[(nextChar == ',') + (2 * (nextChar == '\n'))];
  }
hash_step:
  hash += nextChar;
  hash *= 17;
  hash &= 0xFF;
  goto read_next;

add_hash:
  total += hash;
  hash = 0;
  goto read_next;

eol:
  total += hash;
  printf("%u\n", total);
}
