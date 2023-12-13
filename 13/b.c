#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int totalScore = 0;

  int getlineResult = 500000;

start_next_block:
  int aRows[32] = {0};
  int rowLen = 0;
  int curRow = 0;

  int aCols[32] = {0};
  int colLen = 0;
  int curCol = 0;

  {
    void *aJump[] = {&&load_line_000, &&print_answer};
    goto *aJump[getlineResult <= 0];
  }

load_line_000:
  char *pLine = 0;
  size_t bufSize = 0;
  getlineResult = getline(&pLine, &bufSize, pInput);
load_line_050:
  //
  {
    void *aJump[] = {&&load_line_100, &&block_loaded};
    goto *aJump[getlineResult <= 1];
  }

load_line_100:
  int lineLen = getlineResult - 1;
  curCol = 0;
  pLine[lineLen] = 0;

  aCols[0] <<= 1;
  aCols[1] <<= 1;
  aCols[2] <<= 1;
  aCols[3] <<= 1;
  aCols[4] <<= 1;
  aCols[5] <<= 1;
  aCols[6] <<= 1;
  aCols[7] <<= 1;
  aCols[8] <<= 1;
  aCols[9] <<= 1;
  aCols[10] <<= 1;
  aCols[11] <<= 1;
  aCols[12] <<= 1;
  aCols[13] <<= 1;
  aCols[14] <<= 1;
  aCols[15] <<= 1;
  aCols[16] <<= 1;
  aCols[17] <<= 1;
  aCols[18] <<= 1;
  aCols[19] <<= 1;
  aCols[20] <<= 1;
  aCols[21] <<= 1;
  aCols[22] <<= 1;
  aCols[23] <<= 1;
  aCols[24] <<= 1;
  aCols[25] <<= 1;
  aCols[26] <<= 1;
  aCols[27] <<= 1;
  aCols[28] <<= 1;
  aCols[29] <<= 1;
  aCols[30] <<= 1;
  aCols[31] <<= 1;

  {
    void *aJump[] = {
        &&load_line_100_b0,
        &&load_line_100_b1,
        &&load_line_100_b2,
        &&load_line_100_b3,
        &&load_line_100_b4,
        &&load_line_100_b5,
        &&load_line_100_b6,
        &&load_line_100_b7,
        &&load_line_100_b8,
        &&load_line_100_b9,
        &&load_line_100_b10,
        &&load_line_100_b11,
        &&load_line_100_b12,
        &&load_line_100_b13,
        &&load_line_100_b14,
        &&load_line_100_b15,
        &&load_line_100_b16};
    goto *aJump[lineLen - 1];
  }

#define LOAD_LINE_100_B(num)                                                     \
  load_line_100_b##num : aRows[curRow] |= ((1 << num) * (pLine[curCol] == '#')); \
  aCols[curCol] |= (pLine[curCol] == '#');                                       \
  ++curCol;

  LOAD_LINE_100_B(16);
  LOAD_LINE_100_B(15);
  LOAD_LINE_100_B(14);
  LOAD_LINE_100_B(13);
  LOAD_LINE_100_B(12);
  LOAD_LINE_100_B(11);
  LOAD_LINE_100_B(10);
  LOAD_LINE_100_B(9);
  LOAD_LINE_100_B(8);
  LOAD_LINE_100_B(7);
  LOAD_LINE_100_B(6);
  LOAD_LINE_100_B(5);
  LOAD_LINE_100_B(4);
  LOAD_LINE_100_B(3);
  LOAD_LINE_100_B(2);
  LOAD_LINE_100_B(1);
  LOAD_LINE_100_B(0);

  ++curRow;
  goto load_line_000;

block_loaded:
  rowLen = curRow;
  colLen = curCol;

check_for_row_mirror:
#define CHECK_ROW(offset) smudges += __builtin_popcount(aRows[curRow - offset] ^ aRows[curRow + offset + 1]) * (rowLen > (curRow + offset + 1))
check_for_row_mirror_r1:
  curRow = 0;
  int smudges = 0;
  CHECK_ROW(0);
  int score = 100;
  {
    void *aJump[] = {&&check_for_row_mirror_r2, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r2:
  curRow = 1;
  smudges = 0;
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 200;
  {
    void *aJump[] = {&&check_for_row_mirror_r3, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r3:
  curRow = 2;
  smudges = 0;
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 300;
  {
    void *aJump[] = {&&check_for_row_mirror_r4, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r4:
  curRow = 3;
  smudges = 0;
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 400;
  {
    void *aJump[] = {&&check_for_row_mirror_r5, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r5:
  curRow = 4;
  smudges = 0;
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 500;
  {
    void *aJump[] = {&&check_for_row_mirror_r6, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r6:
  curRow = 5;
  smudges = 0;
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 600;
  {
    void *aJump[] = {&&check_for_row_mirror_r7, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r7:
  curRow = 6;
  smudges = 0;
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 700;
  {
    void *aJump[] = {&&check_for_row_mirror_r8, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r8:
  curRow = 7;
  smudges = 0;
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 800;
  {
    void *aJump[] = {&&check_for_row_mirror_r9, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r9:
  curRow = 8;
  smudges = 0;
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 900;
  {
    void *aJump[] = {&&check_for_row_mirror_r10, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r10:
  curRow = 9;
  smudges = 0;
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1000;
  {
    void *aJump[] = {&&check_for_row_mirror_r11, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r11:
  curRow = 10;
  smudges = 0;
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1100;
  {
    void *aJump[] = {&&check_for_row_mirror_r12, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r12:
  curRow = 11;
  smudges = 0;
  CHECK_ROW(11);
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1200;
  {
    void *aJump[] = {&&check_for_row_mirror_r13, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r13:
  curRow = 12;
  smudges = 0;
  CHECK_ROW(12);
  CHECK_ROW(11);
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1300;
  {
    void *aJump[] = {&&check_for_row_mirror_r14, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r14:
  curRow = 13;
  smudges = 0;
  CHECK_ROW(13);
  CHECK_ROW(12);
  CHECK_ROW(11);
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1400;
  {
    void *aJump[] = {&&check_for_row_mirror_r15, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r15:
  curRow = 14;
  smudges = 0;
  CHECK_ROW(14);
  CHECK_ROW(13);
  CHECK_ROW(12);
  CHECK_ROW(11);
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1500;
  {
    void *aJump[] = {&&check_for_row_mirror_r16, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_row_mirror_r16:
  curRow = 15;
  smudges = 0;
  CHECK_ROW(15);
  CHECK_ROW(14);
  CHECK_ROW(13);
  CHECK_ROW(12);
  CHECK_ROW(11);
  CHECK_ROW(10);
  CHECK_ROW(9);
  CHECK_ROW(8);
  CHECK_ROW(7);
  CHECK_ROW(6);
  CHECK_ROW(5);
  CHECK_ROW(4);
  CHECK_ROW(3);
  CHECK_ROW(2);
  CHECK_ROW(1);
  CHECK_ROW(0);
  score = 1600;
  {
    void *aJump[] = {&&check_for_col_mirror, &&row_mirror_found};
    goto *aJump[smudges == 1];
  }

row_mirror_found:
  totalScore += score;
  goto start_next_block;

check_for_col_mirror:
#define CHECK_COL(offset) smudges += __builtin_popcount(aCols[curCol - offset] ^ aCols[curCol + offset + 1]) * (colLen > (curCol + offset + 1))
check_for_col_mirror_r1:
  curCol = 0;
  smudges = 0;
  CHECK_COL(0);
  score = 1;
  {
    void *aJump[] = {&&check_for_col_mirror_r2, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r2:
  curCol = 1;
  smudges = 0;
  CHECK_COL(1);
  CHECK_COL(0);
  score = 2;
  {
    void *aJump[] = {&&check_for_col_mirror_r3, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r3:
  curCol = 2;
  smudges = 0;
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 3;
  {
    void *aJump[] = {&&check_for_col_mirror_r4, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r4:
  curCol = 3;
  smudges = 0;
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 4;
  {
    void *aJump[] = {&&check_for_col_mirror_r5, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r5:
  curCol = 4;
  smudges = 0;
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 5;
  {
    void *aJump[] = {&&check_for_col_mirror_r6, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r6:
  curCol = 5;
  smudges = 0;
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 6;
  {
    void *aJump[] = {&&check_for_col_mirror_r7, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r7:
  curCol = 6;
  smudges = 0;
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 7;
  {
    void *aJump[] = {&&check_for_col_mirror_r8, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r8:
  curCol = 7;
  smudges = 0;
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 8;
  {
    void *aJump[] = {&&check_for_col_mirror_r9, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r9:
  curCol = 8;
  smudges = 0;
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 9;
  {
    void *aJump[] = {&&check_for_col_mirror_r10, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r10:
  curCol = 9;
  smudges = 0;
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 10;
  {
    void *aJump[] = {&&check_for_col_mirror_r11, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r11:
  curCol = 10;
  smudges = 0;
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 11;
  {
    void *aJump[] = {&&check_for_col_mirror_r12, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r12:
  curCol = 11;
  smudges = 0;
  CHECK_COL(11);
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 12;
  {
    void *aJump[] = {&&check_for_col_mirror_r13, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r13:
  curCol = 12;
  smudges = 0;
  CHECK_COL(12);
  CHECK_COL(11);
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 13;
  {
    void *aJump[] = {&&check_for_col_mirror_r14, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r14:
  curCol = 13;
  smudges = 0;
  CHECK_COL(13);
  CHECK_COL(12);
  CHECK_COL(11);
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 14;
  {
    void *aJump[] = {&&check_for_col_mirror_r15, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r15:
  curCol = 14;
  smudges = 0;
  CHECK_COL(14);
  CHECK_COL(13);
  CHECK_COL(12);
  CHECK_COL(11);
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 15;
  {
    void *aJump[] = {&&check_for_col_mirror_r16, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }
check_for_col_mirror_r16:
  curCol = 15;
  smudges = 0;
  CHECK_COL(15);
  CHECK_COL(14);
  CHECK_COL(13);
  CHECK_COL(12);
  CHECK_COL(11);
  CHECK_COL(10);
  CHECK_COL(9);
  CHECK_COL(8);
  CHECK_COL(7);
  CHECK_COL(6);
  CHECK_COL(5);
  CHECK_COL(4);
  CHECK_COL(3);
  CHECK_COL(2);
  CHECK_COL(1);
  CHECK_COL(0);
  score = 16;
  {
    void *aJump[] = {&&uh_oh, &&col_mirror_found};
    goto *aJump[smudges == 1];
  }

uh_oh:
  assert(!"Uh oh! No row/col found!");

col_mirror_found:
  totalScore += score;
  goto start_next_block;

print_answer:
  printf("%d\n", totalScore);
}
