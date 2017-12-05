#include "cenlib.h"

int main(void) {
    countryADT c = newCountry();
    loadCountry(c);
    freeCountry(c);
    return 0;
}