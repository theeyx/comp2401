#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes
 int stringToInt(char[]);

int main(){
  FILE *fInput, *fOngoing, *fResolved, *fIncomp;
  char buffer[250];
  char rank[5];
  char country[23];
  char totalCases[20];
  char newCases[20];
  char totalDeaths[20];
  char newDeaths[20];
  char totalRecovered[20];
  char activeCases[20];
  char serious[20];
  char totalCasesPerMil[20];
  char deathsPerMil[20];
  char totalTests[20];
  char testsPerMil[20];
  char population[20];

  unsigned int numberOfCases;
  unsigned int numberOfDeaths;
  unsigned int numberOfRecovered;
  unsigned int numberOfPopulation;


  unsigned int dummyUI = 0;
  unsigned short dummyUS = 0;
  unsigned short ongoingCount = 0;
  unsigned short incompleteCount = 0;
  unsigned short resolvedCount = 0;

  char countryCount;

 fInput = fopen("pandemic.tsv", "r");
 if (!fInput) {
   printf("ERROR: Could not open file fInput\n");
   exit(1);
 }

 fOngoing = fopen("ongoing.bin", "wb");
 if (!fOngoing) {
   printf("ERROR: Could not open file fOngoing\n");
   exit(1);
 }

 fResolved = fopen("resolved.bin", "wb");
 if (!fResolved) {
   printf("ERROR: Could not open file fResolved\n");
   exit(1);
 }

 fIncomp = fopen("incomplete.bin", "wb");
 if (!fIncomp) {
   printf("ERROR: Could not open file fIncomp\n");
   exit(1);
 }

 //write unsigned short value of 0 to each binary file as a placeholder.
 fwrite(&dummyUS, sizeof(unsigned short), 1 , fOngoing);
 fwrite(&dummyUS, sizeof(unsigned short), 1 , fResolved);
 fwrite(&dummyUS, sizeof(unsigned short), 1 , fIncomp);


//read and discard the first record
fscanf(fInput,"%[^\n]s",buffer);

char c;
fscanf(fInput,"%[^\t]s",rank);
c = fgetc(fInput);

int result;

while(!feof(fInput)){
    int incomplete = 0;

    country[0] = '\0';
    fscanf(fInput,"%[^\t]s",country);
    c = fgetc(fInput);
    countryCount = (char)strlen(country);


    totalCases[0] = '\0';
    fscanf(fInput,"%[^\t]s",totalCases);
    result = stringToInt(totalCases);
    if(result == -1){
      incomplete = 1;
    }
    numberOfCases = (unsigned int)result;

    c = fgetc(fInput);

    newCases[0] = '\0';
    fscanf(fInput,"%[^\t]s",newCases);
    c = fgetc(fInput);

    totalDeaths[0] = '\0';
    fscanf(fInput,"%[^\t]s",totalDeaths);
    result = stringToInt(totalDeaths);
    if(result == -1){
      incomplete = 1;
    }
    numberOfDeaths = (unsigned int)result;

    c = fgetc(fInput);

    newDeaths[0] = '\0';
    fscanf(fInput,"%[^\t]s",newDeaths);
    c = fgetc(fInput);

    totalRecovered[0] = '\0';
    fscanf(fInput,"%[^\t]s",totalRecovered);
    result = stringToInt(totalRecovered);
    if(result == -1){
      incomplete = 1;
    }
    numberOfRecovered = (unsigned int)result;

    c = fgetc(fInput);

    activeCases[0] = '\0';
    fscanf(fInput,"%[^\t]s",activeCases);
    c = fgetc(fInput);

    serious[0] = '\0';
    fscanf(fInput,"%[^\t]s",serious);
    c = fgetc(fInput);

    totalCasesPerMil[0] = '\0';
    fscanf(fInput,"%[^\t]s",totalCasesPerMil);
    c = fgetc(fInput);

    deathsPerMil[0] = '\0';
    fscanf(fInput,"%[^\t]s",deathsPerMil);
    c = fgetc(fInput);

    totalTests[0] = '\0';
    fscanf(fInput,"%[^\t]s",totalTests);
    c = fgetc(fInput);

    testsPerMil[0] = '\0';
    fscanf(fInput,"%[^\t]s",testsPerMil);
    c = fgetc(fInput);

    population[0] = '\0';
    fscanf(fInput,"%[^\n]s",population);
    result = stringToInt(population);
    if(result == -1){
      incomplete = 1;
    }
    numberOfPopulation = (unsigned int)result;


    //check to see if we need to write to incomplete file
    if(incomplete){
        ++incompleteCount;
        fwrite(&countryCount,sizeof(char),1,fIncomp);
        fwrite(&country,sizeof(char),countryCount,fIncomp);
        fwrite(&numberOfCases,sizeof(unsigned int),1,fIncomp);
        fwrite(&numberOfDeaths,sizeof(unsigned int),1,fIncomp);
        fwrite(&numberOfRecovered,sizeof(unsigned int),1,fIncomp);
        fwrite(&numberOfPopulation,sizeof(unsigned int),1,fIncomp);
    //check to see if we write to resolved file
  }else if(numberOfCases == (numberOfDeaths + numberOfRecovered)){
        ++resolvedCount;
        fwrite(&countryCount,sizeof(char),1,fResolved);
        fwrite(&country,sizeof(char),countryCount,fResolved);
        fwrite(&numberOfDeaths,sizeof(unsigned int),1,fResolved);
        fwrite(&numberOfRecovered,sizeof(unsigned int),1,fResolved);
        fwrite(&numberOfPopulation,sizeof(unsigned int),1,fResolved);

    }else{ //otherwise we write to the ongoing file
        ++ongoingCount;
        char impact;
        double percentImpact = 100.0 * numberOfCases/numberOfPopulation;
        if(percentImpact <= 0.05){
          impact = 'L';
        }else if(percentImpact >= 0.30){
          impact = 'H';
        }else{
          impact = 'M';
        }
        fwrite(&countryCount,sizeof(char),1,fOngoing);
        fwrite(&country,sizeof(char),countryCount,fOngoing);
        fwrite(&numberOfCases,sizeof(unsigned int),1,fOngoing);
        fwrite(&numberOfDeaths,sizeof(unsigned int),1,fOngoing);
        fwrite(&numberOfRecovered,sizeof(unsigned int),1,fOngoing);
        fwrite(&numberOfPopulation,sizeof(unsigned int),1,fOngoing);
        fwrite(&impact,sizeof(char),1,fOngoing);
    }


    rank[0] = '\0';
    fscanf(fInput,"%[^\t]s",rank);
    c = fgetc(fInput);
}

//update counters written at the begining of the file
fseek(fOngoing,0,SEEK_SET);
fwrite(&ongoingCount, sizeof(unsigned short), 1 , fOngoing);
fseek(fResolved,0,SEEK_SET);
fwrite(&resolvedCount, sizeof(unsigned short), 1 , fResolved);
fseek(fIncomp,0,SEEK_SET);
fwrite(&incompleteCount, sizeof(unsigned short), 1 , fIncomp);


fclose(fInput);
fclose(fOngoing);
fclose(fResolved);
fclose(fIncomp);

}


int stringToInt(char inputString[])
{
    if(inputString[0] == '\0'){
        return 0;
    }

    unsigned int total = 0;
    int  i = 0;
    int invalid = 1;
    while(inputString[i] != '\0'){

        if(inputString[i] >= '0' && inputString[i] <= '9'){
            total *= 10;
            total += inputString[i] - '0';
            invalid = 0;
        }
        ++i;
    }
    if(invalid){
        return  -1;
    }else{
        return total;
    }
}
