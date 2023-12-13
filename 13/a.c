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
check_for_row_mirror_r1:
  int match = aRows[0] == aRows[1];
  int score = 100;
  {
    void *aJump[] = {&&check_for_row_mirror_r2, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r2:
  match = (aRows[0] == aRows[3] || rowLen <= 3) &&
          (aRows[1] == aRows[2] && rowLen > 2);
  score = 200;
  {
    void *aJump[] = {&&check_for_row_mirror_r3, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r3:
  match = (aRows[0] == aRows[5] || rowLen <= 5) &&
          (aRows[1] == aRows[4] || rowLen <= 4) &&
          (aRows[2] == aRows[3] && rowLen > 3);
  score = 300;
  {
    void *aJump[] = {&&check_for_row_mirror_r4, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r4:
  match = (aRows[0] == aRows[7] || rowLen <= 7) &&
          (aRows[1] == aRows[6] || rowLen <= 6) &&
          (aRows[2] == aRows[5] || rowLen <= 5) &&
          (aRows[3] == aRows[4] && rowLen > 4);
  score = 400;
  {
    void *aJump[] = {&&check_for_row_mirror_r5, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r5:
  match = (aRows[0] == aRows[9] || rowLen <= 9) &&
          (aRows[1] == aRows[8] || rowLen <= 8) &&
          (aRows[2] == aRows[7] || rowLen <= 7) &&
          (aRows[3] == aRows[6] || rowLen <= 6) &&
          (aRows[4] == aRows[5] && rowLen > 5);
  score = 500;
  {
    void *aJump[] = {&&check_for_row_mirror_r6, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r6:
  match = (aRows[0] == aRows[11] || rowLen <= 11) &&
          (aRows[1] == aRows[10] || rowLen <= 10) &&
          (aRows[2] == aRows[9] || rowLen <= 9) &&
          (aRows[3] == aRows[8] || rowLen <= 8) &&
          (aRows[4] == aRows[7] || rowLen <= 7) &&
          (aRows[5] == aRows[6] && rowLen > 6);
  score = 600;
  {
    void *aJump[] = {&&check_for_row_mirror_r7, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r7:
  match = (aRows[0] == aRows[13] || rowLen <= 13) &&
          (aRows[1] == aRows[12] || rowLen <= 12) &&
          (aRows[2] == aRows[11] || rowLen <= 11) &&
          (aRows[3] == aRows[10] || rowLen <= 10) &&
          (aRows[4] == aRows[9] || rowLen <= 9) &&
          (aRows[5] == aRows[8] || rowLen <= 8) &&
          (aRows[6] == aRows[7] && rowLen > 7);
  score = 700;
  {
    void *aJump[] = {&&check_for_row_mirror_r8, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r8:
  match = (aRows[0] == aRows[15] || rowLen <= 15) &&
          (aRows[1] == aRows[14] || rowLen <= 14) &&
          (aRows[2] == aRows[13] || rowLen <= 13) &&
          (aRows[3] == aRows[12] || rowLen <= 12) &&
          (aRows[4] == aRows[11] || rowLen <= 11) &&
          (aRows[5] == aRows[10] || rowLen <= 10) &&
          (aRows[6] == aRows[9] || rowLen <= 9) &&
          (aRows[7] == aRows[8] && rowLen > 8);
  score = 800;
  {
    void *aJump[] = {&&check_for_row_mirror_r9, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r9:
  match = (aRows[0] == aRows[17] || rowLen <= 17) &&
          (aRows[1] == aRows[16] || rowLen <= 16) &&
          (aRows[2] == aRows[15] || rowLen <= 15) &&
          (aRows[3] == aRows[14] || rowLen <= 14) &&
          (aRows[4] == aRows[13] || rowLen <= 13) &&
          (aRows[5] == aRows[12] || rowLen <= 12) &&
          (aRows[6] == aRows[11] || rowLen <= 11) &&
          (aRows[7] == aRows[10] || rowLen <= 10) &&
          (aRows[8] == aRows[9] && rowLen > 9);
  score = 900;
  {
    void *aJump[] = {&&check_for_row_mirror_r10, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r10:
  match = (aRows[0] == aRows[19] || rowLen <= 19) &&
          (aRows[1] == aRows[18] || rowLen <= 18) &&
          (aRows[2] == aRows[17] || rowLen <= 17) &&
          (aRows[3] == aRows[16] || rowLen <= 16) &&
          (aRows[4] == aRows[15] || rowLen <= 15) &&
          (aRows[5] == aRows[14] || rowLen <= 14) &&
          (aRows[6] == aRows[13] || rowLen <= 13) &&
          (aRows[7] == aRows[12] || rowLen <= 12) &&
          (aRows[8] == aRows[11] || rowLen <= 11) &&
          (aRows[9] == aRows[10] && rowLen > 10);
  score = 1000;
  {
    void *aJump[] = {&&check_for_row_mirror_r11, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r11:
  match = (aRows[0] == aRows[21] || rowLen <= 21) &&
          (aRows[1] == aRows[20] || rowLen <= 20) &&
          (aRows[2] == aRows[19] || rowLen <= 19) &&
          (aRows[3] == aRows[18] || rowLen <= 18) &&
          (aRows[4] == aRows[17] || rowLen <= 17) &&
          (aRows[5] == aRows[16] || rowLen <= 16) &&
          (aRows[6] == aRows[15] || rowLen <= 15) &&
          (aRows[7] == aRows[14] || rowLen <= 14) &&
          (aRows[8] == aRows[13] || rowLen <= 13) &&
          (aRows[9] == aRows[12] || rowLen <= 12) &&
          (aRows[10] == aRows[11] && rowLen > 11);
  score = 1100;
  {
    void *aJump[] = {&&check_for_row_mirror_r12, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r12:
  match = (aRows[0] == aRows[23] || rowLen <= 23) &&
          (aRows[1] == aRows[22] || rowLen <= 22) &&
          (aRows[2] == aRows[21] || rowLen <= 21) &&
          (aRows[3] == aRows[20] || rowLen <= 20) &&
          (aRows[4] == aRows[19] || rowLen <= 19) &&
          (aRows[5] == aRows[18] || rowLen <= 18) &&
          (aRows[6] == aRows[17] || rowLen <= 17) &&
          (aRows[7] == aRows[16] || rowLen <= 16) &&
          (aRows[8] == aRows[15] || rowLen <= 15) &&
          (aRows[9] == aRows[14] || rowLen <= 14) &&
          (aRows[10] == aRows[13] || rowLen <= 13) &&
          (aRows[11] == aRows[12] && rowLen > 12);
  score = 1200;
  {
    void *aJump[] = {&&check_for_row_mirror_r13, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r13:
  match = (aRows[0] == aRows[25] || rowLen <= 25) &&
          (aRows[1] == aRows[24] || rowLen <= 24) &&
          (aRows[2] == aRows[23] || rowLen <= 23) &&
          (aRows[3] == aRows[22] || rowLen <= 22) &&
          (aRows[4] == aRows[21] || rowLen <= 21) &&
          (aRows[5] == aRows[20] || rowLen <= 20) &&
          (aRows[6] == aRows[19] || rowLen <= 19) &&
          (aRows[7] == aRows[18] || rowLen <= 18) &&
          (aRows[8] == aRows[17] || rowLen <= 17) &&
          (aRows[9] == aRows[16] || rowLen <= 16) &&
          (aRows[10] == aRows[15] || rowLen <= 15) &&
          (aRows[11] == aRows[14] || rowLen <= 14) &&
          (aRows[12] == aRows[13] && rowLen > 13);
  score = 1300;
  {
    void *aJump[] = {&&check_for_row_mirror_r14, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r14:
  match = (aRows[0] == aRows[27] || rowLen <= 27) &&
          (aRows[1] == aRows[26] || rowLen <= 26) &&
          (aRows[2] == aRows[25] || rowLen <= 25) &&
          (aRows[3] == aRows[24] || rowLen <= 24) &&
          (aRows[4] == aRows[23] || rowLen <= 23) &&
          (aRows[5] == aRows[22] || rowLen <= 22) &&
          (aRows[6] == aRows[21] || rowLen <= 21) &&
          (aRows[7] == aRows[20] || rowLen <= 20) &&
          (aRows[8] == aRows[19] || rowLen <= 19) &&
          (aRows[9] == aRows[18] || rowLen <= 18) &&
          (aRows[10] == aRows[17] || rowLen <= 17) &&
          (aRows[11] == aRows[16] || rowLen <= 16) &&
          (aRows[12] == aRows[15] || rowLen <= 15) &&
          (aRows[13] == aRows[14] && rowLen > 14);
  score = 1400;
  {
    void *aJump[] = {&&check_for_row_mirror_r15, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r15:
  match = (aRows[0] == aRows[29] || rowLen <= 29) &&
          (aRows[1] == aRows[28] || rowLen <= 28) &&
          (aRows[2] == aRows[27] || rowLen <= 27) &&
          (aRows[3] == aRows[26] || rowLen <= 26) &&
          (aRows[4] == aRows[25] || rowLen <= 25) &&
          (aRows[5] == aRows[24] || rowLen <= 24) &&
          (aRows[6] == aRows[23] || rowLen <= 23) &&
          (aRows[7] == aRows[22] || rowLen <= 22) &&
          (aRows[8] == aRows[21] || rowLen <= 21) &&
          (aRows[9] == aRows[20] || rowLen <= 20) &&
          (aRows[10] == aRows[19] || rowLen <= 19) &&
          (aRows[11] == aRows[18] || rowLen <= 18) &&
          (aRows[12] == aRows[17] || rowLen <= 17) &&
          (aRows[13] == aRows[16] || rowLen <= 16) &&
          (aRows[14] == aRows[15] && rowLen > 15);
  score = 1500;
  {
    void *aJump[] = {&&check_for_row_mirror_r16, &&row_mirror_found};
    goto *aJump[match];
  }
check_for_row_mirror_r16:
  match = (aRows[0] == aRows[31] || rowLen <= 31) &&
          (aRows[1] == aRows[30] || rowLen <= 30) &&
          (aRows[2] == aRows[29] || rowLen <= 29) &&
          (aRows[3] == aRows[28] || rowLen <= 28) &&
          (aRows[4] == aRows[27] || rowLen <= 27) &&
          (aRows[5] == aRows[26] || rowLen <= 26) &&
          (aRows[6] == aRows[25] || rowLen <= 25) &&
          (aRows[7] == aRows[24] || rowLen <= 24) &&
          (aRows[8] == aRows[23] || rowLen <= 23) &&
          (aRows[9] == aRows[22] || rowLen <= 22) &&
          (aRows[10] == aRows[21] || rowLen <= 21) &&
          (aRows[11] == aRows[20] || rowLen <= 20) &&
          (aRows[12] == aRows[19] || rowLen <= 19) &&
          (aRows[13] == aRows[18] || rowLen <= 18) &&
          (aRows[14] == aRows[17] || rowLen <= 17) &&
          (aRows[15] == aRows[16] && rowLen > 16);
  score = 1600;
  {
    void *aJump[] = {&&check_for_col_mirror, &&row_mirror_found};
    goto *aJump[match];
  }

row_mirror_found:
  // printf("%d\n", score);
  totalScore += score;
  goto start_next_block;

check_for_col_mirror:
check_for_col_mirror_r1:
  match = aCols[0] == aCols[1];
  score = 1;
  {
    void *aJump[] = {&&check_for_col_mirror_r2, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r2:
  match = (aCols[0] == aCols[3] || colLen <= 3) &&
          (aCols[1] == aCols[2] && colLen > 2);
  score = 2;
  {
    void *aJump[] = {&&check_for_col_mirror_r3, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r3:
  match = (aCols[0] == aCols[5] || colLen <= 5) &&
          (aCols[1] == aCols[4] || colLen <= 4) &&
          (aCols[2] == aCols[3] && colLen > 3);
  score = 3;
  {
    void *aJump[] = {&&check_for_col_mirror_r4, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r4:
  match = (aCols[0] == aCols[7] || colLen <= 7) &&
          (aCols[1] == aCols[6] || colLen <= 6) &&
          (aCols[2] == aCols[5] || colLen <= 5) &&
          (aCols[3] == aCols[4] && colLen > 4);
  score = 4;
  {
    void *aJump[] = {&&check_for_col_mirror_r5, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r5:
  match = (aCols[0] == aCols[9] || colLen <= 9) &&
          (aCols[1] == aCols[8] || colLen <= 8) &&
          (aCols[2] == aCols[7] || colLen <= 7) &&
          (aCols[3] == aCols[6] || colLen <= 6) &&
          (aCols[4] == aCols[5] && colLen > 5);
  score = 5;
  {
    void *aJump[] = {&&check_for_col_mirror_r6, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r6:
  match = (aCols[0] == aCols[11] || colLen <= 11) &&
          (aCols[1] == aCols[10] || colLen <= 10) &&
          (aCols[2] == aCols[9] || colLen <= 9) &&
          (aCols[3] == aCols[8] || colLen <= 8) &&
          (aCols[4] == aCols[7] || colLen <= 7) &&
          (aCols[5] == aCols[6] && colLen > 6);
  score = 6;
  {
    void *aJump[] = {&&check_for_col_mirror_r7, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r7:
  match = (aCols[0] == aCols[13] || colLen <= 13) &&
          (aCols[1] == aCols[12] || colLen <= 12) &&
          (aCols[2] == aCols[11] || colLen <= 11) &&
          (aCols[3] == aCols[10] || colLen <= 10) &&
          (aCols[4] == aCols[9] || colLen <= 9) &&
          (aCols[5] == aCols[8] || colLen <= 8) &&
          (aCols[6] == aCols[7] && colLen > 7);
  score = 7;
  {
    void *aJump[] = {&&check_for_col_mirror_r8, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r8:
  match = (aCols[0] == aCols[15] || colLen <= 15) &&
          (aCols[1] == aCols[14] || colLen <= 14) &&
          (aCols[2] == aCols[13] || colLen <= 13) &&
          (aCols[3] == aCols[12] || colLen <= 12) &&
          (aCols[4] == aCols[11] || colLen <= 11) &&
          (aCols[5] == aCols[10] || colLen <= 10) &&
          (aCols[6] == aCols[9] || colLen <= 9) &&
          (aCols[7] == aCols[8] && colLen > 8);
  score = 8;
  {
    void *aJump[] = {&&check_for_col_mirror_r9, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r9:
  match = (aCols[0] == aCols[17] || colLen <= 17) &&
          (aCols[1] == aCols[16] || colLen <= 16) &&
          (aCols[2] == aCols[15] || colLen <= 15) &&
          (aCols[3] == aCols[14] || colLen <= 14) &&
          (aCols[4] == aCols[13] || colLen <= 13) &&
          (aCols[5] == aCols[12] || colLen <= 12) &&
          (aCols[6] == aCols[11] || colLen <= 11) &&
          (aCols[7] == aCols[10] || colLen <= 10) &&
          (aCols[8] == aCols[9] && colLen > 9);
  score = 9;
  {
    void *aJump[] = {&&check_for_col_mirror_r10, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r10:
  match = (aCols[0] == aCols[19] || colLen <= 19) &&
          (aCols[1] == aCols[18] || colLen <= 18) &&
          (aCols[2] == aCols[17] || colLen <= 17) &&
          (aCols[3] == aCols[16] || colLen <= 16) &&
          (aCols[4] == aCols[15] || colLen <= 15) &&
          (aCols[5] == aCols[14] || colLen <= 14) &&
          (aCols[6] == aCols[13] || colLen <= 13) &&
          (aCols[7] == aCols[12] || colLen <= 12) &&
          (aCols[8] == aCols[11] || colLen <= 11) &&
          (aCols[9] == aCols[10] && colLen > 10);
  score = 10;
  {
    void *aJump[] = {&&check_for_col_mirror_r11, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r11:
  match = (aCols[0] == aCols[21] || colLen <= 21) &&
          (aCols[1] == aCols[20] || colLen <= 20) &&
          (aCols[2] == aCols[19] || colLen <= 19) &&
          (aCols[3] == aCols[18] || colLen <= 18) &&
          (aCols[4] == aCols[17] || colLen <= 17) &&
          (aCols[5] == aCols[16] || colLen <= 16) &&
          (aCols[6] == aCols[15] || colLen <= 15) &&
          (aCols[7] == aCols[14] || colLen <= 14) &&
          (aCols[8] == aCols[13] || colLen <= 13) &&
          (aCols[9] == aCols[12] || colLen <= 12) &&
          (aCols[10] == aCols[11] && colLen > 11);
  score = 11;
  {
    void *aJump[] = {&&check_for_col_mirror_r12, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r12:
  match = (aCols[0] == aCols[23] || colLen <= 23) &&
          (aCols[1] == aCols[22] || colLen <= 22) &&
          (aCols[2] == aCols[21] || colLen <= 21) &&
          (aCols[3] == aCols[20] || colLen <= 20) &&
          (aCols[4] == aCols[19] || colLen <= 19) &&
          (aCols[5] == aCols[18] || colLen <= 18) &&
          (aCols[6] == aCols[17] || colLen <= 17) &&
          (aCols[7] == aCols[16] || colLen <= 16) &&
          (aCols[8] == aCols[15] || colLen <= 15) &&
          (aCols[9] == aCols[14] || colLen <= 14) &&
          (aCols[10] == aCols[13] || colLen <= 13) &&
          (aCols[11] == aCols[12] && colLen > 12);
  score = 12;
  {
    void *aJump[] = {&&check_for_col_mirror_r13, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r13:
  match = (aCols[0] == aCols[25] || colLen <= 25) &&
          (aCols[1] == aCols[24] || colLen <= 24) &&
          (aCols[2] == aCols[23] || colLen <= 23) &&
          (aCols[3] == aCols[22] || colLen <= 22) &&
          (aCols[4] == aCols[21] || colLen <= 21) &&
          (aCols[5] == aCols[20] || colLen <= 20) &&
          (aCols[6] == aCols[19] || colLen <= 19) &&
          (aCols[7] == aCols[18] || colLen <= 18) &&
          (aCols[8] == aCols[17] || colLen <= 17) &&
          (aCols[9] == aCols[16] || colLen <= 16) &&
          (aCols[10] == aCols[15] || colLen <= 15) &&
          (aCols[11] == aCols[14] || colLen <= 14) &&
          (aCols[12] == aCols[13] && colLen > 13);
  score = 13;
  {
    void *aJump[] = {&&check_for_col_mirror_r14, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r14:
  match = (aCols[0] == aCols[27] || colLen <= 27) &&
          (aCols[1] == aCols[26] || colLen <= 26) &&
          (aCols[2] == aCols[25] || colLen <= 25) &&
          (aCols[3] == aCols[24] || colLen <= 24) &&
          (aCols[4] == aCols[23] || colLen <= 23) &&
          (aCols[5] == aCols[22] || colLen <= 22) &&
          (aCols[6] == aCols[21] || colLen <= 21) &&
          (aCols[7] == aCols[20] || colLen <= 20) &&
          (aCols[8] == aCols[19] || colLen <= 19) &&
          (aCols[9] == aCols[18] || colLen <= 18) &&
          (aCols[10] == aCols[17] || colLen <= 17) &&
          (aCols[11] == aCols[16] || colLen <= 16) &&
          (aCols[12] == aCols[15] || colLen <= 15) &&
          (aCols[13] == aCols[14] && colLen > 14);
  score = 14;
  {
    void *aJump[] = {&&check_for_col_mirror_r15, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r15:
  match = (aCols[0] == aCols[29] || colLen <= 29) &&
          (aCols[1] == aCols[28] || colLen <= 28) &&
          (aCols[2] == aCols[27] || colLen <= 27) &&
          (aCols[3] == aCols[26] || colLen <= 26) &&
          (aCols[4] == aCols[25] || colLen <= 25) &&
          (aCols[5] == aCols[24] || colLen <= 24) &&
          (aCols[6] == aCols[23] || colLen <= 23) &&
          (aCols[7] == aCols[22] || colLen <= 22) &&
          (aCols[8] == aCols[21] || colLen <= 21) &&
          (aCols[9] == aCols[20] || colLen <= 20) &&
          (aCols[10] == aCols[19] || colLen <= 19) &&
          (aCols[11] == aCols[18] || colLen <= 18) &&
          (aCols[12] == aCols[17] || colLen <= 17) &&
          (aCols[13] == aCols[16] || colLen <= 16) &&
          (aCols[14] == aCols[15] && colLen > 15);
  score = 15;
  {
    void *aJump[] = {&&check_for_col_mirror_r16, &&col_mirror_found};
    goto *aJump[match];
  }
check_for_col_mirror_r16:
  match = (aCols[0] == aCols[31] || colLen <= 31) &&
          (aCols[1] == aCols[30] || colLen <= 30) &&
          (aCols[2] == aCols[29] || colLen <= 29) &&
          (aCols[3] == aCols[28] || colLen <= 28) &&
          (aCols[4] == aCols[27] || colLen <= 27) &&
          (aCols[5] == aCols[26] || colLen <= 26) &&
          (aCols[6] == aCols[25] || colLen <= 25) &&
          (aCols[7] == aCols[24] || colLen <= 24) &&
          (aCols[8] == aCols[23] || colLen <= 23) &&
          (aCols[9] == aCols[22] || colLen <= 22) &&
          (aCols[10] == aCols[21] || colLen <= 21) &&
          (aCols[11] == aCols[20] || colLen <= 20) &&
          (aCols[12] == aCols[19] || colLen <= 19) &&
          (aCols[13] == aCols[18] || colLen <= 18) &&
          (aCols[14] == aCols[17] || colLen <= 17) &&
          (aCols[15] == aCols[16] && colLen > 16);
  score = 16;
  {
    void *aJump[] = {&&uh_oh, &&col_mirror_found};
    goto *aJump[match];
  }

uh_oh:
  assert(!"Uh oh! No row/col found!");

col_mirror_found:
  // printf("%d\n", score);
  totalScore += score;
  goto start_next_block;

print_answer:
  printf("%d\n", totalScore);
}
