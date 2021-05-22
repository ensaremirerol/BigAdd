//
// Created by ensar on 5/19/2021.
//
#include <stdio.h>
#include "linetrckr.h"

#ifndef LEXICAL_WIN_FILEIO_H
#define LEXICAL_WIN_FILEIO_H
#define EOL '.'
#define WHITE_SPACE ' '
#define COMMENT_OPEN '{'
#define COMMENT_CLOSE '}'
#define SEPERATOR ','
#define LEXEME_STRING '"'

// Opens file
FILE *openFile(char *path, char *mode) {
    FILE *fPtr;
    fPtr = fopen(path, mode);
    if (fPtr) return fPtr;
    else {
        perror(path);
        exit(1);
    }
}

// Clears given char array
void strclr(char *str, const int BUFFER_SIZE) {
    for (int i = 0; i < BUFFER_SIZE + 1; i++) str[i] = 0;
}

bool skipIgnoreChars(FILE *fPtr, LineTracker *tracker) {
    bool result = false;
    char c = (char) fgetc(fPtr);
    if (c == WHITE_SPACE || c == '\n' || c == '\r') result = true;
    while (c == WHITE_SPACE || c == '\n' || c == '\r') {
        if (c == '\n') incrementLine(tracker);
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

void getWord(char *out, FILE *fPtr, LineTracker *tracker, const int BUFFER_SIZE) {
    strclr(out, BUFFER_SIZE);
    while (skipCommentBlocks(fPtr, tracker) || skipIgnoreChars(fPtr, tracker));
    char c = (char) fgetc(fPtr);

    if (feof(fPtr)) exit(0);

    if (c != EOL && c != SEPERATOR && c != LEXEME_STRING) {
        for (int i = 0; c != EOL && c != WHITE_SPACE && c != SEPERATOR && c != '\n'; i++) {
            if(c == EOF) return;
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        ungetc(c, fPtr);
        out[strlen(out)] = '\0';
        return;
    }
    else if(c == LEXEME_STRING){
        out[0] = c;
        c = (char) fgetc(fPtr);
        for (int i = 1; c != LEXEME_STRING; i++) {
            if(c == EOF) return;
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        out[strlen(out)] = c;
        out[strlen(out)] = '\0';
        return;
    }
    out[0] = c;
}

#endif //LEXICAL_WIN_FILEIO_H
