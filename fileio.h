//
// Created by ensar on 5/19/2021.
//
#include <stdio.h>
#ifndef LEXICAL_WIN_FILEIO_H
#define LEXICAL_WIN_FILEIO_H
#define EOL '.'
#define WHITE_SPACE ' '
#define COMMENT_OPEN '{'
#define COMMENT_CLOSE '}'
#define SEPERATOR ','
// Opens file
FILE* openFile(char* path, char* mode){
    FILE* fPtr;
    fPtr = fopen(path, mode);
    if(fPtr) return fPtr;
    else{
        perror("Error");
        exit(1);
    }
}

// Clears given char array
void strclr(char* str, int size){
    for (int i = 0; i < size; i++)
    {
        str[i] = 0;
    }
}

bool skipIgnoreChars(FILE* fPtr, int* currLine){
    bool result = false;
    char c = (char) fgetc(fPtr);
    if(c == WHITE_SPACE || c == '\n' || c == '\r') result = true;
    while (c == WHITE_SPACE || c == '\n' || c == '\r'){
        if(c == '\n') currLine++;
        c = (char) fgetc(fPtr);
    }
    ungetc(c, fPtr);
    return result;
}

bool skipCommentBlocks(FILE* fPtr, int* currLine){
    int lineIncrement = 0;
    bool result = false;
    char c = (char) fgetc(fPtr);
    if(c == COMMENT_OPEN){
        result = true;
        while(c != COMMENT_CLOSE){
            if(feof(fPtr)){
                fprintf(stderr, "Comment do not closed at line: %d", *currLine);
                exit(4);
            }
            else if(c == '\n') lineIncrement++;
            c = (char) fgetc(fPtr);
        }
        *currLine += lineIncrement;
    }
    else ungetc(c, fPtr);
    return result;
}

void getWord(char* out, FILE* fPtr, int* currLine, const int BUFFER_SIZE){
    strclr(out, BUFFER_SIZE);
    while (skipCommentBlocks(fPtr, currLine) || skipIgnoreChars(fPtr, currLine));
    char c = (char) fgetc(fPtr);
    if(feof(fPtr)){
        exit(0);
    }
    if( c != EOL && c != SEPERATOR){
        for (int i = 0; c != EOL && c != WHITE_SPACE && c != SEPERATOR && c != '\n'; i++){
            out[i] = c;
            c = (char) fgetc(fPtr);
        }
        ungetc(c, fPtr);
        out[strlen(out)] = '\0';
        return;
    }
    out[0] = c;
}
#endif //LEXICAL_WIN_FILEIO_H
