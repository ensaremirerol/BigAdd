//
// Created by ensar on 5/24/2021.
//
#include <stdio.h>
#include "fileio.h"
#ifndef LEXICAL_REWRITE_ERRHANDLE_H
#define LEXICAL_REWRITE_ERRHANDLE_H

void err(char* format, char* word, int line, unsigned char* flag, char* expectedKeycode, FILE *fPtr){
    fprintf(stderr, format, word, line);
    *flag = LINE_ENDED;
    *expectedKeycode = -1;
    seekEOL(fPtr);
}
#endif //LEXICAL_REWRITE_ERRHANDLE_H
