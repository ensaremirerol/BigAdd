//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_WORD_H
#define BIGADD_WORD_H
#define BUFFER_SIZE 255
#include <stdbool.h>
#include <stdlib.h>
#include "str.h"

typedef struct wordStruct{
    char* word;
    unsigned int size;
    bool isExpanded;
}Word;

Word* createWord();

void expandWord(Word* word);

void shrinkWord(Word* word);

void freeWord(Word* word);

#endif //BIGADD_WORD_H
