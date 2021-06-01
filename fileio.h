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

// Skips all ignored characters. If it skips a character/s, returns true.
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
// Skips comment blocks. If it skips a comment block, returns true.
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
// This is a bit spaghetti function :/
// Gets a word from the file
void getWord(char *out, FILE *fPtr, LineTracker *tracker, const int BUFFER_SIZE) {
    strclr(out, BUFFER_SIZE); // Clear given pointer
    // Skip all ignore chars and comment blocks.
    while (skipCommentBlocks(fPtr, tracker) || skipIgnoreChars(fPtr, tracker));
    // Get a char from the file
    char c = (char) fgetc(fPtr);
    if (feof(fPtr)) return;
    // If the read char is not one of them, read until another ignore char
    if (c != EOL && c != SEPERATOR && c != LEXEME_STRING && c != OPEN_BLOCK && c != CLOSE_BLOCK) {
        for (int i = 0;
             c != EOL && c != WHITE_SPACE && c != SEPERATOR && c != '\n' && c != '\r' && c != '\t'
             && c != OPEN_BLOCK && c != CLOSE_BLOCK; i++) {
            if (c == EOF) return;
            if(i >= BUFFER_SIZE -1){
                fprintf(stderr, "Analyzers' buffer overflowed at line %d", getLine(tracker));
                exit(-1);
            }
            // This is an exception
            // If a word is adjacent to a string it reads until another LEXEME_STRING(")
            if(c == LEXEME_STRING){
                out[i] = c;
                c = (char) fgetc(fPtr);
                for (int j = i+1; j < BUFFER_SIZE-1 && c!=LEXEME_STRING; ++j) {
                    if (c == EOF) return;
                    if(i >= BUFFER_SIZE -1){
                        fprintf(stderr, "Analyzers' buffer overflowed at line %d", getLine(tracker));
                        exit(-1);
                    }
                    out[j] = c;
                    c = (char) fgetc(fPtr);
                }
                out[strlen(out)] = c;
                out[strlen(out)] = '\0';
                return;
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
    // If the read char is EOL, SEPERATOR, OPEN_BLOCK or CLOSE_BLOCK then function returns only that char.
    out[0] = c;
}

void seekEOL(char* word, FILE *fPtr, LineTracker *tracker, const int BUFFER_SIZE) {
    getWord(word, fPtr, tracker, BUFFER_SIZE);
    if (feof(fPtr)) return;
    while (strcmp(word, ".") != 0) getWord(word, fPtr, tracker, BUFFER_SIZE);
}

#endif //LEXICAL_FILEIO_H
