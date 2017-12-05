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
void loadCountry(const countryADT c);

/*
**
*/
void makeCountry(const countryADT c);

/*
**
*/
void makeProvince(const countryADT c);

/*
**
*/
void makeApartment(const countryADT c);

/*
**
*/
void freeCountry(const countryADT c);


#endif