#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//define structs
typedef struct{
  unsigned int numberOfCases;
  char country[23];
} countryStats;

//function prototypes
int compare(const void *,const void *);

int main() {
  FILE *fInOngoing, *fInResolved, *fInIncomp;

  setlocale(LC_NUMERIC, "");

  char country[23];

  unsigned short ongoingCount = 0;
  unsigned short incompleteCount = 0;
  unsigned short resolvedCount = 0;

  unsigned int numberOfCases;
  unsigned int numberOfDeaths;
  unsigned int numberOfRecovered;
  unsigned int numberOfPopulation;

  char countryCount;
  char impact;

  unsigned long long totalWorldPop = 0;
  unsigned int totalCasesWW = 0;
  unsigned int totalDeathsWW = 0;
  unsigned int totalRecoveredWW = 0;
  unsigned int totalOngoingCasesWW = 0;



  fInOngoing = fopen("ongoing.bin", "rb");
  if (!fInOngoing) {
    printf("ERROR: Could not open file fInOngoing\n");
    exit(1);
  }

  fInResolved = fopen("resolved.bin", "rb");
  if (!fInResolved) {
    printf("ERROR: Could not open file fInResolved\n");
    exit(1);
  }

  fInIncomp = fopen("incomplete.bin", "rb");
  if (!fInIncomp) {
    printf("ERROR: Could not open file fInIncomp\n");
    exit(1);
  }

//  REPORT FOR ONGOING CASES
printf("%30s%20s%17s%15s%16s   %6s\n","Country","Cases","Deaths","Recovered","Population","Impact");
printf("%30s%20s%17s%15s%16s   %6s\n","------------------------------","--------------","--------------","------------","-------------","------");
fread(&ongoingCount,sizeof(unsigned short),1,fInOngoing);

//dynamically allocate array for country stats
countryStats* statsArray = (countryStats*)malloc((unsigned short)ongoingCount*sizeof(countryStats));

for(int i = 1; i<=ongoingCount; ++i){
  fread(&countryCount,sizeof(char),1,fInOngoing);
  fread(country,sizeof(char),countryCount,fInOngoing);
  country[countryCount] = '\0';

  fread(&numberOfCases,sizeof(unsigned int),1,fInOngoing);
  fread(&numberOfDeaths,sizeof(unsigned int),1,fInOngoing);
  fread(&numberOfRecovered,sizeof(unsigned int),1,fInOngoing);
  fread(&numberOfPopulation,sizeof(unsigned int),1,fInOngoing);
  fread(&impact,sizeof(char),1,fInOngoing);

  statsArray[i-1].numberOfCases = numberOfCases;
  strcpy(statsArray[i-1].country,country);

  totalWorldPop += numberOfPopulation;
  totalCasesWW += numberOfCases;
  totalDeathsWW += numberOfDeaths;
  totalRecoveredWW += numberOfRecovered;
  totalOngoingCasesWW += numberOfCases - numberOfDeaths - numberOfRecovered;

  printf("%30s%'20u%'17u%'15u%'16u   %c \n",country,numberOfCases,numberOfDeaths,numberOfRecovered,numberOfPopulation,impact  );
}

puts("\n");

//  REPORT FOR RESOLVED CASES
printf("%30s%20s%17s%15s%16s\n","Country","Cases","Deaths","Recovered","Population");
printf("%30s%20s%17s%15s%16s\n","------------------------------","--------------","--------------","------------","-------------");
fread(&resolvedCount,sizeof(unsigned short),1,fInResolved);
for(int i = 1; i<=resolvedCount; ++i){
  fread(&countryCount,sizeof(char),1,fInResolved);
  fread(country,sizeof(char),countryCount,fInResolved);
  country[countryCount] = '\0';

  fread(&numberOfDeaths,sizeof(unsigned int),1,fInResolved);
  fread(&numberOfRecovered,sizeof(unsigned int),1,fInResolved);
  fread(&numberOfPopulation,sizeof(unsigned int),1,fInResolved);

  totalWorldPop += numberOfPopulation;
  totalCasesWW += numberOfDeaths+numberOfRecovered;
  totalDeathsWW += numberOfDeaths;
  totalRecoveredWW += numberOfRecovered;

  printf("%30s%'20u%'17u%'15u%'16u\n",country,(numberOfDeaths+numberOfRecovered),numberOfDeaths,numberOfRecovered,numberOfPopulation);
}

puts("\n");

//  REPORT FOR INCOMPLETE CASES
printf("%30s%20s%17s%15s%16s\n","Country","Cases","Deaths","Recovered","Population");
printf("%30s%20s%17s%15s%16s\n","------------------------------","--------------","--------------","------------","-------------");
fread(&incompleteCount,sizeof(unsigned short),1,fInIncomp);
for(int i = 1; i<=incompleteCount; ++i){
  fread(&countryCount,sizeof(char),1,fInIncomp);
  fread(country,sizeof(char),countryCount,fInIncomp);
  country[countryCount] = '\0';

  fread(&numberOfCases,sizeof(unsigned int),1,fInIncomp);
  fread(&numberOfDeaths,sizeof(unsigned int),1,fInIncomp);
  fread(&numberOfRecovered,sizeof(unsigned int),1,fInIncomp);
  fread(&numberOfPopulation,sizeof(unsigned int),1,fInIncomp);

  printf("%30s",country);

  if(numberOfCases == -1){
    printf("%20s","---");
  }else{
    printf("%'20u",numberOfCases);
  }

  if(numberOfDeaths == -1){
    printf("%17s","---");
  }else{
    printf("%'17u",numberOfDeaths);
  }

  if(numberOfRecovered == -1){
    printf("%15s","---");
  }else{
    printf("%'15u",numberOfRecovered);
  }

  if(numberOfPopulation == -1){
    printf("%16s\n","---");
  }else{
    printf("%'16u\n",numberOfPopulation);
  }
}


  puts("\n");


  printf("The total world population for which we have complete statistics is : %'llu\n",totalWorldPop);
  printf("The total number of cases worldwide is : %'u\n",totalCasesWW);
  printf("The percentage of total number of cases worldwide is : %'.2f\n", 100.0 * totalCasesWW/totalWorldPop);
  printf("The total number of deaths worldwide is : %'u\n",totalDeathsWW);
  printf("The percentage of total number of deaths worldwide is : %'.2f\n", 100.0 * totalDeathsWW/totalCasesWW);
  printf("The total number of recovered worldwide is : %'u\n",totalRecoveredWW);
  printf("The percentage of total number of recovered worldwide is : %'.2f\n", 100.0 * totalRecoveredWW/totalCasesWW);
  printf("The total number of ongoing cases worldwide is : %'u\n",totalOngoingCasesWW);
  printf("The percentage of total number of ongoing cases worldwide is : %'.2f\n", 100.0 * totalOngoingCasesWW/totalCasesWW);

  puts("\n");

  printf("%10s     %s\n","TOTAL CASES", "COUNTRY");
  printf("%10s     %s\n","-----------", "-------");
  qsort(statsArray,ongoingCount,sizeof(countryStats),compare);
  for(int i = 0; i<ongoingCount; ++i){
    printf("%'11d     %s\n",statsArray[i].numberOfCases, statsArray[i].country);
  }

  free(statsArray); //free memory that was dynamically allocated

  fclose(fInOngoing);
  fclose(fInResolved);
  fclose(fInIncomp);
}

//compare function for qsort
int compare(const void * lPtr,const void * rPtr){
  return ((countryStats*)rPtr)->numberOfCases - ((countryStats*)lPtr)->numberOfCases;
}
