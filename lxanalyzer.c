//
// Created by ensar on 6/8/2021.
//

#include "lxanalyzer.h"


TokenType lexicalAnalyzer(LexicalData* data, KeyWord *root){
    if(feof(data->fPtr)) return bEOF;

    getWord(data->currWord, data->fPtr, &data->currLine);

    if(strcmp(data->currWord->word, "") == 0) return bEOF;

    data->currKeyword = getKeyWord(data->currWord->word, root);

    if(data->currKeyword) return bKeyword;

    if(isStringConstant(data->currWord->word, &data->currLine)) return bStringConstant;

    if (isIntConstant(data->currWord->word)) return bIntConstant;

    if (isIdentifier(data->currWord->word)) return bIdentifier;

    return bError;
}

void freeLexicalData(LexicalData* data){
    fclose(data->fPtr);
    freeWord(data->currWord);
    free(data);
}