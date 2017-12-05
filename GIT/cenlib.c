#include "cenlib.h"
#include "auxlib.h"

struct Inhabitant {
    unsigned char condition;
    unsigned long homeID;
    char apName[MAXLINE - BLOCKQTY], provName[MAXLINE - BLOCKQTY];
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

struct Inhabitant parseData(char * str);
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

struct Inhabitant parseData(char * str) {
    struct Inhabitant h;
    char seps[]   = ",\n";
    char * token = strtok(str, seps);
    int idx = 0;
    while (token != NULL) {
        if(idx == 0) sscanf(token, "%c", &h.condition);
        if(idx == 1) sscanf(token, "%lu", &h.homeID);
        if(idx == 2) sscanf(token, "%[^\t\n]", h.apName);
        if(idx == 3) sscanf(token, "%[^\t\n]", h.provName);
        idx++;
        token = strtok(NULL, seps);
    }
    return h;
}

countryADT newCountry(void) {
    countryADT c = reserveMemory(sizeof(*c), NULL);
    return c;
}

void loadCountry(countryADT c) {
    char line[MAXLINE - BLOCKQTY];
    while(getline(line, MAXLINE-BLOCKQTY) != EOF) {
        struct Inhabitant h = parseData(line);
        c->ctyQuantity++;
        c->status[charToInt(h.condition)]++;
        c->firstProv = addOrEdit(c->firstProv, h);
    }
}

struct Province * addOrEdit(struct Province * p, struct Inhabitant h) {
    if(p == NULL || (strcmp(h.provName, p->provName) < 0)) {

    } else if(strcmp(h.provName, p->provName) == 0) {
        p->prvQuantity++;
        p->status[charToInt(h.condition)]++;
    }
}