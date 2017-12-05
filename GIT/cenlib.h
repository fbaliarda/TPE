#ifndef CENLIB_H
#define CENLIB_H

typedef struct Country * countryADT;

/* 
**
*/
countryADT newCountry(void);

/*
**
*/
void loadCountry(countryADT c);

/*
**
*/
void freeCountry(const countryADT c);

#endif