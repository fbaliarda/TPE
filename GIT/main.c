#include "cenlib.h"
#include "auxlib.h"

#define PATH "/home/franco/censo.csv"
int main(void) {
    char line[MAXLINE],apName[MAXLINE],provName[MAXLINE];
    char c,condition;
    unsigned long homeID;
    int index = 0;
    inhabitantADT inhabitant;
    countryADT country = newCountry();

    while((c = getchar()) != EOF) {
    	if( c != '\n') 
    		line[index++] = c;
    	else {
    		index = 0;
    		sscanf(line,"%c,%lu,%s,%s",&condition,&homeID,apName,provName);
    		inhabitant = newInhabitant(condition,homeID,apName,provName);
    		addInhabitant(country,inhabitant);
    	}
    }
    return 0;
}