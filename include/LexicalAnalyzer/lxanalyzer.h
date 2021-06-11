//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_LXANALYZER_H
#define BIGADD_LXANALYZER_H

#include "../Word/word.h"
#include "../KeyWord/keyword.h"
#include "../File_IO/fileio.h"
#include <stdio.h>
#include <string.h>

typedef struct lexicalDataKeeper{
    FILE* fPtr;
    Word* currWord;
    KeyWord *currKeyword;
    unsigned int currLine;
}LexicalData;

TokenType lexicalAnalyzer(LexicalData* data, KeyWord *root);

void freeLexicalData(LexicalData* data);

#endif //BIGADD_LXANALYZER_H
