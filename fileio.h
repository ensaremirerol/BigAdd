//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_FILEIO_H
#define BIGADD_FILEIO_H
#define EOL '.'
#define WHITE_SPACE ' '
#define COMMENT_OPEN '{'
#define COMMENT_CLOSE '}'
#define SEPARATOR ','
#define LEXEME_STRING '"'
#define OPEN_BLOCK '['
#define CLOSE_BLOCK ']'
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "str.h"

// Opens file
FILE *openFile(char *path, char *mode);

// Skips all ignored characters. If it skips a character/s, returns true.
bool skipIgnoreChars(FILE *fPtr, unsigned int *line);

// Skips comment blocks. If it skips a comment block, returns true.
bool skipCommentBlocks(FILE *fPtr, unsigned int *line);

// Gets a word from the file
void getWord(Word *word, FILE *fPtr, unsigned int *line);


#endif //BIGADD_FILEIO_H
