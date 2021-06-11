//
// Created by ensar on 6/8/2021.
//

#include "../../include/Word/word.h"

Word* createWord(){
    Word* word = malloc(sizeof (Word));
    word->word = malloc(BUFFER_SIZE);
    word->size = BUFFER_SIZE;
    word->isExpanded = false;
    return word;
}

void expandWord(Word* word){
    char* tmp;
    unsigned int newSize = word->size * 2;
    for (int i = 0; i < 10; i++) {
        tmp = (char*) realloc(word->word, newSize);
        if(tmp){
            // Clears the new allocated memory
            // (tmp + word->size) -> Start point of newly allocated memory
            strclr((tmp+word->size), word->size);
            word->word = tmp;
            word->size = newSize;
            word->isExpanded = true;
            return;
        }
    }
    perror("Reallocation error:");
    exit(-1);
}

void shrinkWord(Word* word){
    char* tmp;
    for (int i = 0; i < 10; i++) {
        tmp = (char*) realloc(word->word, BUFFER_SIZE);
        if(tmp){
            // Clears the new allocated memory
            strclr(tmp, BUFFER_SIZE);
            word->word = tmp;
            word->size = BUFFER_SIZE;
            word->isExpanded = false;
            return;
        }
    }
    perror("Reallocation error:");
    exit(-1);
}

void freeWord(Word* word){
    free(word->word);
    free(word);
}