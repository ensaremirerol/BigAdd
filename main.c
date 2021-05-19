#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fileio.h"
#include "keyword.h"

#define BUFFER_SIZE 255

//TODO fix line counting
/*
 *  EXIT CODES
 *  0 OKAY
 *  1 FILE OPERATION ERROR
 *  2 FILE READ ERROR
 *  3 UNRECOGNIZED KEYWORD
 *  4 NOT CLOSED LEXEME
 *  5 CL ARGUMENT ERROR
 */

int main(int argc, char** argv) {
    char* fPath;
    if(argc == 1){
        fprintf(stderr, "You must enter file");
        exit(5);
    }
    else if(argc > 2){
        fprintf(stderr, "Do not enter more than one argument");
        exit(5);
    }
    else{
        fPath = *(argv + 1);
    }
    KeyWord* keyWordRoot;
    keyWordRoot = createKeyWordLinkedList();
    // Files
    FILE* fPtr = openFile(fPath, "r");
    FILE* wPtr = openFile("./lexical.lx", "w");
    int currLine = 1;
    char* currWord;
    currWord = malloc(BUFFER_SIZE);
    while (true){
        if(feof(fPtr)) break;
        getWord(currWord, fPtr, &currLine, BUFFER_SIZE);
        switch (getKeyCode(currWord, keyWordRoot))
        {
            case 0:
                fprintf(wPtr, "Keyword int\n");
                break;
            case 1:
                fprintf(wPtr, "Keyword move\n");
                break;
            case 2:
                fprintf(wPtr, "Keyword add\n");
                break;
            case 3:
                fprintf(wPtr, "Keyword sub\n");
                break;
            case 4:
                fprintf(wPtr, "Keyword out\n");
                break;
            case 5:
                fprintf(wPtr, "Keyword loop\n");
                break;
            case 6:
                fprintf(wPtr, "OpenBlock\n");
                break;
            case 7:
                fprintf(wPtr, "CloseBlock\n");
                break;
            case 8:
                fprintf(wPtr, "Keyword times\n");
                break;
            case 9:
                fprintf(wPtr, "Keyword newline\n");
                break;
            case 10:
                fprintf(wPtr, "Keyword to\n");
                break;
            case 11:
                fprintf(wPtr, "EndOfLine\n");
                break;
            case 12:
                fprintf(wPtr, "Separator\n");
                break;
            default:
                if(isStringConstant(currWord, currLine)){
                    fprintf(wPtr, "StringConstant %s\n", currWord);
                }
                else if(isIntConstant(currWord)){
                    fprintf(wPtr, "IntConstant %s\n", currWord);
                }
                else if(isVariable(currWord)){
                    fprintf(wPtr, "Identifier %s\n", currWord);
                }
                else{
                    fprintf(stderr,"\nUnrecognized keyword \"%s\", at line %d\n", currWord, currLine);
                    exit(3);
                }
                break;
        }
    }
    fclose(fPtr);
    fclose(wPtr);
    free(currWord);
    freeKeyWordLinkedList(keyWordRoot);
    return 0;
}
