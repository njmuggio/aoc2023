#include <stdio.h>

int main(int argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  int aTimes[4] = {0};
  int timesCount = 0;
  int aDistances[4] = {0};
  int distancesCount = 0;

  long margin = 1;

  fscanf(pInput, "Time: ");

  int scanfResult = fscanf(pInput, "%d", &aTimes[timesCount]);
  timesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aTimes[timesCount]);
  timesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aTimes[timesCount]);
  timesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aTimes[timesCount]);
  timesCount += scanfResult == 1;

  fscanf(pInput, " Distance:");

  scanfResult = fscanf(pInput, "%d", &aDistances[distancesCount]);
  distancesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aDistances[distancesCount]);
  distancesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aDistances[distancesCount]);
  distancesCount += scanfResult == 1;
  scanfResult = fscanf(pInput, "%d", &aDistances[distancesCount]);
  distancesCount += scanfResult == 1;

  int curRaceIdx = 0;
process_race:
  // All races processed?
  {
    void *aJump[] = {&&process_race_000, &&print_result};
    goto *aJump[curRaceIdx == timesCount];
  }
process_race_000:
  int sleepTime = aTimes[curRaceIdx];
  int winCount = 0;
process_race_100:
  int distance = (aTimes[curRaceIdx] - sleepTime) * sleepTime;
  winCount += (distance > aDistances[curRaceIdx]);

  --sleepTime;

  // All sleep times checked?
  {
    void *aJump[] = {&&process_race_100, &&process_race_200};
    goto *aJump[sleepTime < 0];
  }
process_race_200:
  margin *= winCount;
  ++curRaceIdx;
  goto process_race;

print_result:
  printf("%ld\n", margin);

  return 0;
}
