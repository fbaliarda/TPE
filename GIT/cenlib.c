#include "cenlib.h"
#include "auxlib.h"

struct Inhabitant {
    unsigned char condition;
    unsigned long homeID;
    char apName[MAXLINE], provName[MAXLINE];
};

struct Apartment {
    char * apName;
    unsigned int aptQuantity;
    char status[4];
    struct Apartment * next;
};

struct Province {
    char * provName;
    unsigned int prvQuantity;
    char status[4];
    struct Apartment * first;
    struct Province * next;
};

struct Country {
    unsigned int ctyQuantity;
    int status[4];
    struct Province * firstProv;
};


void freeProvince(struct Province * p);
void freeApartments(struct Apartment * apt);
void * reserveMemory(size_t bytes, countryADT c);

void freeCountry(const countryADT c) {
    if(c == NULL) return;
    freeProvince(c->firstProv);
    free(c);
}

void freeProvince(struct Province * p) {
    if(p == NULL) return;
    freeProvince(p->next);
    freeApartments(p->first);
    free(p->provName);
    free(p);
}

void freeApartments(struct Apartment * apt) {
    if(apt == NULL) return;
    freeApartments(apt->next);
    free(apt->apName);
    free(apt);
}

void * reserveMemory(size_t bytes, countryADT c) {
    void * r = calloc(1, bytes);
    if(r == NULL) {
        fprintf(stderr, "ERROR:::No se pudo reservar memoria.");
        freeCountry(c);
        exit(1);
    }
    return r;
}

inhabitantADT newInhabitant(char condition, unsigned long homeID, char* apName, char* provName){
    inhabitantADT h = calloc(1,sizeof(*h));
    if(h == NULL) {
        fprintf(stderr, "ERROR:::No se pudo reservar memoria.");
        exit(1);
    }
    h->condition = condition;
    h->homeID = homeID;
    strcpy(h->apName,apName);
    strcpy(h->provName,provName);
    return h;
}

countryADT newCountry(void) {
    countryADT c = reserveMemory(sizeof(*c), NULL);
    return c;
}

struct Province * addOrEdit(struct Province * p, struct Inhabitant h) {
    if(p == NULL || (strcmp(h.provName, p->provName) < 0)) {

    } else if(strcmp(h.provName, p->provName) == 0) {
        p->prvQuantity++;
        p->status[h.condition]++;
    }
    return p;
}

void addInhabitant(countryADT c, inhabitantADT h) {
    c->ctyQuantity++;
    c->status[charToInt(h->condition)]++;
    c->firstProv = addOrEdit(c->firstProv, *h);
}

void freeInhabitant(inhabitantADT h) {
    if(h != NULL)
        free(h);
}
