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

static struct Apartment * addOrEditApt(struct Apartment * a, struct Inhabitant h);
static struct Province * addOrEditProv(struct Province * p, struct Inhabitant h);
static struct Inhabitant parseData(char * str);
static void freeProvince(struct Province * p);
static void freeApartments(struct Apartment * apt);
static void * reserveMemory(size_t bytes, countryADT c);

void freeCountry(const countryADT c) {
    if(c == NULL) return;
    freeProvince(c->firstProv);
    free(c);
}

static void freeProvince(struct Province * p) {
    if(p == NULL) return;
    freeProvince(p->next);
    freeApartments(p->first);
    free(p->provName);
    free(p);
}

static void freeApartments(struct Apartment * apt) {
    if(apt == NULL) return;
    freeApartments(apt->next);
    free(apt->apName);
    free(apt);
}

static void * reserveMemory(size_t bytes, countryADT c) {
    void * r = calloc(1, bytes);
    if(r == NULL) {
        fprintf(stderr, "ERROR:::No se pudo reservar memoria.");
        freeCountry(c);
        exit(1);
    }
    return r;
}

static struct Inhabitant parseData(char * str) {
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
    if(c == NULL) {
        fprintf(stderr, "ERROR:::Se debe reservar memoria para un objeto countryADT.");
        exit(1);
    }
    char line[MAXLINE - BLOCKQTY];
    while(getline(line, MAXLINE-BLOCKQTY) != EOF) {
        struct Inhabitant h = parseData(line);
        c->ctyQuantity++;
        c->status[charToInt(h.condition)]++;
        c->firstProv = addOrEditProv(c->firstProv, h);
    }
    struct Province * iter = c->firstProv;
    while(iter != NULL) {
        struct Apartment * iter2 = iter->first;
        printf("Provincia %s hay -> Sin datos:%i Ocupada:%i Desocupada:%i Economicamente Inactiva:%i\n", iter->provName, iter->status[0], iter->status[1],iter->status[2],iter->status[3]);
        while(iter2 != NULL) {
            printf("\t->Departamento %s hay -> Sin datos:%i Ocupada:%i Desocupada:%i Economicamente Inactiva:%i\n", iter2->apName, iter2->status[0], iter2->status[1],iter2->status[2],iter2->status[3]);
            iter2 = iter2->next;
        }
        iter = iter->next;
    }
}

static struct Province * addOrEditProv(struct Province * p, struct Inhabitant h) {
    if(p == NULL || (strcmp(h.provName, p->provName) < 0)) {
        struct Province * aux = calloc(1, sizeof(*aux));
        aux->provName = malloc(strlen(h.provName)+1);
        strcpy(aux->provName, h.provName);
        aux->prvQuantity = aux->status[charToInt(h.condition)] = 1;
        aux->next = p;
        aux->first = addOrEditApt(aux->first, h);
        return aux;
    } else if(strcmp(h.provName, p->provName) == 0) {
        p->prvQuantity++;
        p->status[charToInt(h.condition)]++;
        p->first = addOrEditApt(p->first, h);
        return p;
    }
    p->next = addOrEditProv(p->next, h);
    return p;
}

static struct Apartment * addOrEditApt(struct Apartment * a, struct Inhabitant h) {
    if(a == NULL || (strcmp(h.apName, a->apName) < 0)) {
        struct Apartment * aux = calloc(1, sizeof(*aux));
        aux->apName = malloc(strlen(h.apName) + 1);
        strcpy(aux->apName, h.apName);
        aux->aptQuantity = aux->status[charToInt(h.condition)] = 1;
        aux->next = a;
        return aux;
    } else if(strcmp(h.apName, a->apName) == 0) {
        a->aptQuantity++;
        a->status[charToInt(h.condition)]++;
        return a;
    }
    a->next = addOrEditApt(a->next, h);
    return a;
}