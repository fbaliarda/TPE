#include "auxlib.h"

FILE * openFile(char * path, char * permisos) {
    FILE * f = fopen(path, permisos);
    if(f == NULL) {
        fprintf(stderr, "ERROR:::No se pudo abrir el archivo.");
        exit(-1);
    }
    return f;
}

int getline(char line[], int max) {
    int nch = 0;
    int c;
    max = max - 1;
    while((c = getchar()) != EOF)
	    {
	    if(c == '\n')
		    break;

	    if(nch < max) line[nch++] = c;
	}

    if(c == EOF && nch == 0)
	    return EOF;

    line[nch] = '\0';
    return nch;
}

