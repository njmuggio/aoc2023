#include <stdio.h>

int main(int argc, char **pArgv)
{
  long time = 0;
  long record = 0;

  long aTimes[] = {71530, 58819676};
  long aRecords[] = {940200, 434104122191218l};

  time = aTimes[pArgv[1][0] == 'i'];
  record = aRecords[pArgv[1][0] == 'i'];

  long sleepTime = -1;

search_first_over:
  ++sleepTime;
  long dist = (time - sleepTime) * sleepTime;
  {
    void *aJump[] = {&&search_first_over, &&found_first_over};
    goto *aJump[dist > record];
  }

found_first_over:
  printf("%ld\n", 1 + time - (2 * sleepTime));
}
