//
// Created by ensar on 5/19/2021.
//
#include <stdio.h>
#include "linetrckr.h"

#ifndef LEXICAL_FILEIO_H
#define LEXICAL_FILEIO_H
#define EOL '.'
#define WHITE_SPACE ' '
#define COMMENT_OPEN '{'
#define COMMENT_CLOSE '}'
#define SEPERATOR ','
#define LEXEME_STRING '"'
#define OPEN_BLOCK '['
#define CLOSE_BLOCK ']'

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
void strclr(char *str, const int BUFFER_SIZE) {
    for (int i = 0; i < BUFFER_SIZE; i++) str[i] = 0;
}

bool skipIgnoreChars(FILE *fPtr, LineTracker *tracker) {
    bool result = false;
    char c = (char) fgetc(fPtr);
    if (c == WHITE_SPACE || c == '\n' || c == '\r' || c == '\t') result = true;
    while (c == WHITE_SPACE || c == '\n' || c == '\r' || c == '\t') {
        if (feof(fPtr)) return false;
        else if (c == '\n') incrementLine(tracker);
        c = (char) fgetc(fPtr);
    }
    ungetc(c, fPtr);
    return result;
}

bool skipCommentBlocks(FILE *fPtr, LineTracker *tracker) {
    int lineStarted = getLine(tracker);
    bool result = false;
    char c = (char) fgetc(fPtr);
    if (c == COMMENT_OPEN) {
        result = true;
        while (c != COMMENT_CLOSE) {
            if (feof(fPtr)) {
                fprintf(stderr, "Comment do not closed at line: %d", lineStarted);
                exit(4);
            } else if (c == '\n') incrementLine(tracker);
            c = (char) fgetc(fPtr);
        }
    } else ungetc(c, fPtr);
    return result;
}

void seekEOL(FILE *fPtr, LineTracker *tracker) {
    char c = (char) fgetc(fPtr);
    if (feof(fPtr)) return;
    while (c != EOL) {
        if (c == '\n') incrementLine(tracker);
        c = (char) fgetc(fPtr);
    }
}

void getWord(char *out, FILE *fPtr, LineTracker *tracker, const int BUFFER_SIZE) {
    strclr(out, BUFFER_SIZE);
    while (skipCommentBlocks(fPtr, tracker) || skipIgnoreChars(fPtr, tracker));
    char c = (char) fgetc(fPtr);

    if (feof(fPtr)) return;

    if (c != EOL && c != SEPERATOR && c != LEXEME_STRING && c != OPEN_BLOCK && c != CLOSE_BLOCK) {

        for (int i = 0;
             c != EOL && c != WHITE_SPACE && c != SEPERATOR && c != '\n' && c != '\r' && c != '\t' && c != LEXEME_STRING
             && c != OPEN_BLOCK && c != CLOSE_BLOCK; i++) {
            if (c == EOF) return;
            if(i >= BUFFER_SIZE -1){
                fprintf(stderr, "Analyzers' buffer overflowed at line %d", getLine(tracker));
                exit(-1);
            }
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        ungetc(c, fPtr);
        out[strlen(out)] = '\0';
        return;
    } else if (c == LEXEME_STRING) {
        out[0] = c;
        c = (char) fgetc(fPtr);
        for (int i = 1; c != LEXEME_STRING; i++) {
            if (c == EOF) return;
            if(i >= BUFFER_SIZE -1){
                fprintf(stderr, "Analyzers' buffer overflowed at line %d", getLine(tracker));
                exit(-1);
            }
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        out[strlen(out)] = c;
        out[strlen(out)] = '\0';
        return;
    }
    out[0] = c;
}

#endif //LEXICAL_FILEIO_H
