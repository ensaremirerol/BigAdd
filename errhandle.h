//
// Created by ensar on 5/24/2021.
//
#include <stdio.h>
#include "fileio.h"
#ifndef LEXICAL_ERRHANDLE_H
#define LEXICAL_ERRHANDLE_H

void err(char* format, char* word, int line, unsigned char* flag, char* expectedKeycode, FILE *fPtr, LineTracker* tracker){
    fprintf(stderr, format, word, line);
    *flag = LINE_ENDED;
    *expectedKeycode = -1;
    seekEOL(fPtr, tracker);
}
#endif //LEXICAL_ERRHANDLE_H
