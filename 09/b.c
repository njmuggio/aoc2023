#include <stdio.h>
#include <string.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  long totalExtrapolated = 0;

  long aSeq[64][128];

process_next_sequence:
  memset(aSeq, 0, sizeof(aSeq));
  int seqLen = 0;
  char *pLine = 0;
  size_t lineSize = 0;
  int charsRead = 0;
  int offset = 0;
read_next_input:
  ssize_t getlineResult = getline(&pLine, &lineSize, pInput);
  {
    void *aJump[] = {&&read_next_input_000, &&end_of_inputs};
    goto *aJump[getlineResult < 0];
  }
read_next_input_000:
  int scanfResult = sscanf(pLine + offset, "%ld%n", &aSeq[0][64 + seqLen++], &charsRead);
  {
    void *aJump[] = {&&read_next_input_100, &&process_sequence};
    goto *aJump[scanfResult != 1];
  }
read_next_input_100:
  offset += charsRead;
  goto read_next_input_000;

process_sequence:
  --seqLen;
  int workRowNum = 0;
  int workRowLen = seqLen;
  int workRowIdx = 0;
  int nonZeroFound = 0;

build_next_row:
  ++workRowNum;
  --workRowLen;
  workRowIdx = 64;
  nonZeroFound = 0;

populate_next_cell:
  aSeq[workRowNum][workRowIdx] = aSeq[workRowNum - 1][workRowIdx + 1] - aSeq[workRowNum - 1][workRowIdx];
  nonZeroFound |= aSeq[workRowNum][workRowIdx] != 0;
  ++workRowIdx;
  {
    void *aJump[] = {&&extrapolate_or_continue, &&populate_next_cell};
    goto *aJump[workRowIdx < workRowLen + 64];
  }

extrapolate_or_continue:
{
  void *aJump[] = {&&extrapolate, &&build_next_row};
  goto *aJump[nonZeroFound];
}

extrapolate:
  --workRowNum;
  workRowIdx = 63;
  aSeq[workRowNum][workRowIdx] = aSeq[workRowNum][workRowIdx + 1] - aSeq[workRowNum + 1][workRowIdx];
  {
    void *aJump[] = {&&extrapolate, &&extrapolation_complete};
    goto *aJump[workRowNum == 0];
  }

extrapolation_complete:
  totalExtrapolated += aSeq[workRowNum][63];
  goto process_next_sequence;

end_of_inputs:
  printf("%ld\n", totalExtrapolated);
}
