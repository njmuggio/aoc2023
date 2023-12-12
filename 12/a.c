#include <stdio.h>
#include <string.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int aReq[6];
  int reqLen;

  char aBitDescBuf[21];
  int bitDescLen;

  unsigned int totalValidOptions = 0;

load_line_000:
  memset(aBitDescBuf, 0, sizeof(aBitDescBuf));
  reqLen = 0;
  int scanfResult = fscanf(pInput, "%s%n", aBitDescBuf, &bitDescLen);
  {
    void *aJump[] = {&&load_line_100, &&all_lines_processed};
    goto *aJump[scanfResult < 0];
  }

load_line_100:
  bitDescLen = strlen(aBitDescBuf);
  unsigned int curBits =
      (1 << 19) * (aBitDescBuf[19] == '#') +
      (1 << 18) * (aBitDescBuf[18] == '#') +
      (1 << 17) * (aBitDescBuf[17] == '#') +
      (1 << 16) * (aBitDescBuf[16] == '#') +
      (1 << 15) * (aBitDescBuf[15] == '#') +
      (1 << 14) * (aBitDescBuf[14] == '#') +
      (1 << 13) * (aBitDescBuf[13] == '#') +
      (1 << 12) * (aBitDescBuf[12] == '#') +
      (1 << 11) * (aBitDescBuf[11] == '#') +
      (1 << 10) * (aBitDescBuf[10] == '#') +
      (1 << 9) * (aBitDescBuf[9] == '#') +
      (1 << 8) * (aBitDescBuf[8] == '#') +
      (1 << 7) * (aBitDescBuf[7] == '#') +
      (1 << 6) * (aBitDescBuf[6] == '#') +
      (1 << 5) * (aBitDescBuf[5] == '#') +
      (1 << 4) * (aBitDescBuf[4] == '#') +
      (1 << 3) * (aBitDescBuf[3] == '#') +
      (1 << 2) * (aBitDescBuf[2] == '#') +
      (1 << 1) * (aBitDescBuf[1] == '#') +
      (1 << 0) * (aBitDescBuf[0] == '#');

  unsigned int mask =
      (1 << 19) * (aBitDescBuf[19] == '#' || aBitDescBuf[19] == '?') +
      (1 << 18) * (aBitDescBuf[18] == '#' || aBitDescBuf[18] == '?') +
      (1 << 17) * (aBitDescBuf[17] == '#' || aBitDescBuf[17] == '?') +
      (1 << 16) * (aBitDescBuf[16] == '#' || aBitDescBuf[16] == '?') +
      (1 << 15) * (aBitDescBuf[15] == '#' || aBitDescBuf[15] == '?') +
      (1 << 14) * (aBitDescBuf[14] == '#' || aBitDescBuf[14] == '?') +
      (1 << 13) * (aBitDescBuf[13] == '#' || aBitDescBuf[13] == '?') +
      (1 << 12) * (aBitDescBuf[12] == '#' || aBitDescBuf[12] == '?') +
      (1 << 11) * (aBitDescBuf[11] == '#' || aBitDescBuf[11] == '?') +
      (1 << 10) * (aBitDescBuf[10] == '#' || aBitDescBuf[10] == '?') +
      (1 << 9) * (aBitDescBuf[9] == '#' || aBitDescBuf[9] == '?') +
      (1 << 8) * (aBitDescBuf[8] == '#' || aBitDescBuf[8] == '?') +
      (1 << 7) * (aBitDescBuf[7] == '#' || aBitDescBuf[7] == '?') +
      (1 << 6) * (aBitDescBuf[6] == '#' || aBitDescBuf[6] == '?') +
      (1 << 5) * (aBitDescBuf[5] == '#' || aBitDescBuf[5] == '?') +
      (1 << 4) * (aBitDescBuf[4] == '#' || aBitDescBuf[4] == '?') +
      (1 << 3) * (aBitDescBuf[3] == '#' || aBitDescBuf[3] == '?') +
      (1 << 2) * (aBitDescBuf[2] == '#' || aBitDescBuf[2] == '?') +
      (1 << 1) * (aBitDescBuf[1] == '#' || aBitDescBuf[1] == '?') +
      (1 << 0) * (aBitDescBuf[0] == '#' || aBitDescBuf[0] == '?');

  unsigned int upperBound = (1 << bitDescLen) - 1;

  memset(aReq, 0, sizeof(aReq));

load_line_200:
  fscanf(pInput, "%d", &aReq[reqLen++]);
  int commaRead = 0;
  scanfResult = fscanf(pInput, ",%n", &commaRead);
  {
    void *aJump[] = {&&load_line_200, &&reqs_loaded};
    goto *aJump[commaRead == 0];
  }

reqs_loaded:
  unsigned int countOffset = 0;
  unsigned int popcountExpected = aReq[0] + aReq[1] + aReq[2] + aReq[3] + aReq[4] + aReq[5];

check_next_val_0000:
  unsigned int candidateVal = curBits + countOffset++;
  unsigned int bak = candidateVal;
  unsigned int popcountActual = __builtin_popcount(candidateVal);
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000};
    goto *aJump[(popcountExpected == popcountActual) && ((candidateVal & ~mask) == 0) && ((candidateVal & curBits) == curBits)];
  }

check_next_val_1000:
{
  void *aJump[] = {&&check_next_val_1000_check_req_0,
                   &&check_next_val_1000_check_req_1,
                   &&check_next_val_1000_check_req_2,
                   &&check_next_val_1000_check_req_3,
                   &&check_next_val_1000_check_req_4,
                   &&check_next_val_1000_check_req_5};
  goto *aJump[reqLen - 1];
}

check_next_val_1000_check_req_5:
  int lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  int lo = __builtin_clrsb(candidateVal) + 1;
  candidateVal <<= lo;
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000_check_req_4};
    goto *aJump[lo == aReq[5]];
  }

check_next_val_1000_check_req_4:
  lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  lo = __builtin_clrsb(candidateVal) + 1;
  candidateVal <<= lo;
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000_check_req_3};
    goto *aJump[lo == aReq[4]];
  }

check_next_val_1000_check_req_3:
  lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  lo = __builtin_clrsb(candidateVal) + 1;
  candidateVal <<= lo;
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000_check_req_2};
    goto *aJump[lo == aReq[3]];
  }

check_next_val_1000_check_req_2:
  lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  lo = __builtin_clrsb(candidateVal) + 1;
  candidateVal <<= lo;
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000_check_req_1};
    goto *aJump[lo == aReq[2]];
  }

check_next_val_1000_check_req_1:
  lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  lo = __builtin_clrsb(candidateVal) + 1;
  candidateVal <<= lo;
  {
    void *aJump[] = {&&check_next_val_9000, &&check_next_val_1000_check_req_0};
    goto *aJump[lo == aReq[1]];
  }

check_next_val_1000_check_req_0:
  lz = __builtin_clz(candidateVal);
  candidateVal <<= lz;
  lo = __builtin_clrsb(candidateVal) + 1;
  totalValidOptions += lo == aReq[0];

check_next_val_9000:
{
  void *aJump[] = {&&check_next_val_0000, &&load_line_000};
  goto *aJump[bak >= upperBound];
}

all_lines_processed:
  printf("%u\n", totalValidOptions);
}
