//
// Created by ensar on 6/8/2021.
//

#include "fileio.h"

// Opens file
FILE *openFile(char *path, char *mode) {
    FILE *fPtr;
    fPtr = fopen(path, mode);
    if (fPtr) return fPtr;
    else {
        perror(path);
        return NULL;
    }
}

// Clears given char array
void strclr(char* str, unsigned int size) {
    for (int i = 0; i < size; i++) str[i] = 0;
}

// Skips all ignored characters. If it skips a character/s, returns true.
bool skipIgnoreChars(FILE *fPtr, unsigned int *line) {
    bool result = false;
    char c = (char) fgetc(fPtr);
    if (c == WHITE_SPACE || c == '\n' || c == '\r' || c == '\t') result = true;
    while (c == WHITE_SPACE || c == '\n' || c == '\r' || c == '\t') {
        if (feof(fPtr)) return false;
        else if (c == '\n') *line += 1;
        c = (char) fgetc(fPtr);
    }
    ungetc(c, fPtr);
    return result;
}

// Skips comment blocks. If it skips a comment block, returns true.
bool skipCommentBlocks(FILE *fPtr, unsigned int *line) {
    unsigned int lineStarted = *line;
    bool result = false;
    char c = (char) fgetc(fPtr);
    if (c == COMMENT_OPEN) {
        result = true;
        while (c != COMMENT_CLOSE) {
            if (feof(fPtr)) {
                fprintf(stderr, "Comment do not closed at line: %d\n", lineStarted);
                exit(1);
            } else if (c == '\n') *line += 1;
            c = (char) fgetc(fPtr);
        }
    } else ungetc(c, fPtr);
    return result;
}

// This is a bit spaghetti function :/
// Gets a word from the file
void getWord(Word *word, FILE *fPtr, unsigned int *line) {
    if(word->isExpanded){
        shrinkWord(word);
    }
    else strclr(word->word, word->size);
    // Skip all ignore chars and comment blocks.
    char *out = word->word;
    while (skipCommentBlocks(fPtr, line) || skipIgnoreChars(fPtr, line));
    // Get a char from the file
    char c = (char) fgetc(fPtr);
    if (feof(fPtr)) return;
    // If the read char is not one of them, read until another ignore char
    if (c != EOL && c != SEPARATOR && c != LEXEME_STRING && c != OPEN_BLOCK && c != CLOSE_BLOCK) {
        for (int i = 0;
             c != EOL && c != WHITE_SPACE && c != SEPARATOR && c != '\n' && c != '\r' && c != '\t'
             && c != OPEN_BLOCK && c != CLOSE_BLOCK && c != LEXEME_STRING && c != COMMENT_OPEN; i++) {
            if (c == EOF) return;
            if(i >= word->size -1){
                expandWord(word);
                out = word->word;
            }
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        out[strlen(out)] = 0;
        ungetc(c, fPtr);
        return;
    } else if (c == LEXEME_STRING) {
        out[0] = c;
        c = (char) fgetc(fPtr);
        for (int i = 1; c != LEXEME_STRING; i++) {
            if (c == EOF) return;
            if(i >= word->size - 2){
                expandWord(word);
                out = word->word;
            }
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        out[strlen(out)] = c;
        out[strlen(out)] = '\0';
        return;
    }
    // If the read char is EOL, SEPARATOR, OPEN_BLOCK or CLOSE_BLOCK then function returns only that char.
    out[0] = c;
    out[1] = 0;
}