#ifndef BibArquivos_h
#define BibArquivos_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 172 //A maior palavra do mundo tem 173 letras

int contalinhas(char * pesq);
FILE *openFile(char *pointerFileName);
void huntWords(FILE *arq, FILE * uarq, char *pesq);
void userMenu(char *textOne, char * textTwo, char * dictFile);



#endif
