#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct MapEntry_t
{
  long source;
  long dest;
  long len;
} MapEntry;

long main(long argc, char **pArgv)
{
  FILE *pInput = fopen(pArgv[1], "r");

  long aInitialSeeds[20];
  long initialSeedCount = 0;
  memset(aInitialSeeds, 0, sizeof(aInitialSeeds));

  MapEntry aSeedSoil[100];
  long seedSoilCount = 0;
  memset(aSeedSoil, 0, sizeof(aSeedSoil));

  MapEntry aSoilFert[100];
  long soilFertCount = 0;
  memset(aSoilFert, 0, sizeof(aSoilFert));

  MapEntry aFertWater[100];
  long fertWaterCount = 0;
  memset(aFertWater, 0, sizeof(aFertWater));

  MapEntry aWaterLight[100];
  long waterLightCount = 0;
  memset(aWaterLight, 0, sizeof(aWaterLight));

  MapEntry aLightTemp[100];
  long lightTempCount = 0;
  memset(aLightTemp, 0, sizeof(aLightTemp));

  MapEntry aTempHum[100];
  long tempHumCount = 0;
  memset(aTempHum, 0, sizeof(aTempHum));

  MapEntry aHumLoc[100];
  long humLocCount = 0;
  memset(aHumLoc, 0, sizeof(aHumLoc));

  long scanfResult = fscanf(pInput, "seeds: ");

read_initial_seed_lp:
  scanfResult = fscanf(pInput, "%ld", &aInitialSeeds[initialSeedCount++]);
  {
    void *aJumpTable[] = {&&end_read_initial_seed_lp, &&read_initial_seed_lp};
    goto *aJumpTable[scanfResult];
  }
end_read_initial_seed_lp:
  --initialSeedCount;

#define READ_MAP(mapName, counter, label)                                                                                                     \
  fscanf(pInput, label);                                                                                                                      \
  read_##mapName##_lp : scanfResult = fscanf(pInput, "%ld %ld %ld", &mapName[counter].dest, &mapName[counter].source, &mapName[counter].len); \
  ++counter;                                                                                                                                  \
  {                                                                                                                                           \
    void *aJumpTable[] = {&&end_read_##mapName##_lp, &&read_##mapName##_lp};                                                                  \
    goto *aJumpTable[scanfResult == 3];                                                                                                       \
  }                                                                                                                                           \
  end_read_##mapName##_lp : --counter;

  READ_MAP(aSeedSoil, seedSoilCount, "seed-to-soil map:");
  READ_MAP(aSoilFert, soilFertCount, "soil-to-fertilizer map:");
  READ_MAP(aFertWater, fertWaterCount, "fertilizer-to-water map:");
  READ_MAP(aWaterLight, waterLightCount, "water-to-light map:");
  READ_MAP(aLightTemp, lightTempCount, "light-to-temperature map:");
  READ_MAP(aTempHum, tempHumCount, "temperature-to-humidity map:");
  READ_MAP(aHumLoc, humLocCount, "humidity-to-location map:");

  long curSeed = 0;
  long curSoil = -1;
  long curFert = -1;
  long curWater = -1;
  long curLight = -1;
  long curTemp = -1;
  long curHum = -1;
  long curLoc = -1;

  long curSeedIdx = 0;
  long curMapIdx = 0;

  long offsetInBucket = 0;
  long bucketDiff = 0;

  long minLoc = INT_MAX;

process_seed:
  // all seeds processed?
  {
    void *aJumpTable[] = {&&process_seed_100, &&end_process_seed};
    goto *aJumpTable[curSeedIdx == initialSeedCount];
  }
process_seed_100:
  curSeed = aInitialSeeds[curSeedIdx];

#define SEARCH_MAP(mapName, mapLen, mapFromVar, mapToVar)                                                                                 \
  find_##mapName : curMapIdx = 0;                                                                                                         \
  mapToVar = mapFromVar;                                                                                                                  \
  find_##mapName##_000:                                                                                                                   \
  {                                                                                                                                       \
    void *aJumpTable[] = {&&find_##mapName##_100, &&end_find_##mapName};                                                                  \
    goto *aJumpTable[curMapIdx == mapLen];                                                                                                \
  }                                                                                                                                       \
  find_##mapName##_100:                                                                                                                   \
  {                                                                                                                                       \
    long curMapEntryMatch = mapName[curMapIdx].source <= mapFromVar && mapFromVar < (mapName[curMapIdx].source + mapName[curMapIdx].len); \
    void *aJumpTable[] = {&&find_##mapName##_200, &&find_##mapName##_300};                                                                \
    goto *aJumpTable[curMapEntryMatch];                                                                                                   \
  }                                                                                                                                       \
  find_##mapName##_200 : ++curMapIdx;                                                                                                     \
  goto find_##mapName##_000;                                                                                                              \
  find_##mapName##_300 : bucketDiff = mapName[curMapIdx].dest - mapName[curMapIdx].source;                                                \
  mapToVar += bucketDiff;                                                                                                                 \
  end_find_##mapName:

  SEARCH_MAP(aSeedSoil, seedSoilCount, curSeed, curSoil);
  SEARCH_MAP(aSoilFert, soilFertCount, curSoil, curFert);
  SEARCH_MAP(aFertWater, fertWaterCount, curFert, curWater);
  SEARCH_MAP(aWaterLight, waterLightCount, curWater, curLight);
  SEARCH_MAP(aLightTemp, lightTempCount, curLight, curTemp);
  SEARCH_MAP(aTempHum, tempHumCount, curTemp, curHum);
  SEARCH_MAP(aHumLoc, humLocCount, curHum, curLoc);

  long aLocCandidates[] = {minLoc, curLoc};
  minLoc = aLocCandidates[curLoc < minLoc];
  ++curSeedIdx;
  goto process_seed;

end_process_seed:
  printf("%ld\n", minLoc);

  return 0;
}
