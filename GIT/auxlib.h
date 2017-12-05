#ifndef AUXLIB_H
#define AUXLIB_H

#define charToInt(x) (x - '0')
#define MAXLINE 80
#define BLOCKQTY 4

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE * openFile(char * path, char * action);
int getline(char line[], int max);

#endif
