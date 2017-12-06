#include "cenlib.h"
#include "auxlib.h"


int main(void) {
    char line[MAXLINE],apName[MAXLINE],provName[MAXLINE];
    char condition;
    unsigned long homeID;
    inhabitantADT inhabitant;
    countryADT country = newCountry();

    while((getline(line,MAXLINE)) != EOF) {
    	sscanf(line,"%c,%lu,%s,%s",&condition,&homeID,apName,provName);
	inhabitant = newInhabitant(condition,homeID,apName,provName);
	addInhabitant(country,inhabitant);
	printf("%c,%lu,%s,%s",condition,homeID,apName,provName);
	freeInhabitant(inhabitant);
    }
    freeCountry(country);
    return 0;
}
