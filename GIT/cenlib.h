#ifndef CENLIB_H
#define CENLIB_H

typedef struct Country * countryADT;
typedef struct Inhabitant * inhabitantADT;
/* 
**
*/
countryADT newCountry(void);
/*
**
*/
inhabitantADT newInhabitant(char condition, unsigned long homeID, char* apName, char* provName);
/*
**
*/
void addInhabitant(countryADT c, inhabitantADT h);
/*
**
*/
void freeCountry(const countryADT c);
/*
**
*/
void freeInhabitant(inhabitantADT h);

#endif