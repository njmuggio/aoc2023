#include <stdio.h>
#include <string.h>

typedef struct Lens_t
{
  char aLabel[7];
  int lensType;
} Lens;

int main(int argc, char **pArgv)
{
  Lens aLensMap[256][1000];
  memset(aLensMap, 0, sizeof(aLensMap));
  char aLabel[7];
  int labelLen = 0;

  void *pRetAddr = 0;
  unsigned hash = 0;
  unsigned idx = 0;

  goto real_main;

find_label_in_box:
  idx = 0;
find_label_in_box_000:
{
  void *aJump[] = {&&find_label_in_box_100, &&find_label_in_box_900};
  goto *aJump[(aLensMap[hash][idx].aLabel[0] == 0) || (strcmp(aLensMap[hash][idx].aLabel, aLabel) == 0)];
}
find_label_in_box_100:
  ++idx;
  goto find_label_in_box_000;

find_label_in_box_900:
  goto *pRetAddr;

real_main:
  FILE *pInput = fopen(pArgv[1], "r");

next_lens:
  memset(aLabel, 0, sizeof(aLabel));
  hash = 0;
  labelLen = 0;

read_next_char:
  unsigned char nextChar = getc(pInput);
  {
    void *aJump[] = {&&hash_step, &&remove_label, &&add_label};
    goto *aJump[(nextChar == '-') + (2 * (nextChar == '='))];
  }
hash_step:
  aLabel[labelLen++] = nextChar;
  hash += nextChar;
  hash *= 17;
  hash &= 0xFF;
  goto read_next_char;

remove_label:
  pRetAddr = &&remove_label_100;
  goto find_label_in_box;
remove_label_100:
{
  void *aJump[] = {&&remove_label_200, &&check_for_end};
  goto *aJump[aLensMap[hash][idx].aLabel[0] == 0];
}
remove_label_200:
  memmove(aLensMap[hash] + idx, aLensMap[hash] + idx + 1, sizeof(Lens) * (1000 - idx));
  memset(aLensMap[hash] + 999, 0, sizeof(Lens));
  goto check_for_end;

add_label:
  int lensType = getc(pInput) - '0';
  pRetAddr = &&add_label_100;
  goto find_label_in_box;
add_label_100:
  memcpy(aLensMap[hash][idx].aLabel, aLabel, sizeof(aLabel));
  aLensMap[hash][idx].lensType = lensType;
  goto check_for_end;

check_for_end:
  nextChar = getc(pInput);
  {
    void *aJump[] = {&&next_lens, &&end_of_input};
    goto *aJump[nextChar == '\n'];
  }

end_of_input:
  int total = 0;
  hash = 0;
hash_lp_000:
  idx = 0;
idx_lp_000:
  total += (hash + 1) * (idx + 1) * aLensMap[hash][idx++].lensType;
  {
    void *aJump[] = {&&idx_lp_000, &&idx_lp_999};
    goto *aJump[aLensMap[hash][idx].aLabel[0] == 0];
  }
idx_lp_999:
{
  void *aJump[] = {&&hash_lp_000, &&hash_lp_999};
  goto *aJump[++hash == 256];
}
hash_lp_999:
  printf("%d\n", total);
}
