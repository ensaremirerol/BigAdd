#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fileio.h"
#include "keyword.h"
#include "errhandle.h"
#define BUFFER_SIZE 255
int main(int argc, char** argv) {
    char *fPath;
    char *wPath;
    unsigned char flags = LINE_ENDED;
    char expectedKeyCode = -1;
    int blockCount = 0;
    if (argc == 1) {
        fprintf(stderr, "You must enter file");
        exit(5);
    } else if (argc > 2) {
        fprintf(stderr, "Do not enter more than one argument");
        exit(5);
    } else {
        fPath = *(argv + 1);
        size_t len = strlen(fPath);
        wPath = (char*) malloc((sizeof(char) * len ) + 1);
        strcpy(wPath, fPath);
        len = strlen(wPath);
        wPath[len - 1] = 'x';
        wPath[len - 2] = 'l';
    }
    KeyWord* currKeyWord;
    KeyWord *keyWordRoot;
    keyWordRoot = createKeyWordLinkedList();
    // Files
    FILE *fPtr = openFile(fPath, "r");
    FILE *wPtr = openFile(wPath, "w");
    LineTracker *tracker;
    tracker = createLineTracker();
    char *currWord;
    currWord = malloc(BUFFER_SIZE);

    while(true){
        if(feof(fPtr)) break;
        getWord(currWord, fPtr, tracker, BUFFER_SIZE);
        currKeyWord = getKeyWord(currWord, keyWordRoot);
        if(currKeyWord && (flags & OUT_LIST) != 0 && currKeyWord->keycode != 9){
            err("\nUnexpected keyword \"%s\", at line %d\n", currWord, getLine(tracker), &flags, &expectedKeyCode, fPtr);
            continue;
        }
        if((currKeyWord && (flags & currKeyWord->flagsForKeyword) == currKeyWord->flagsForKeyword &&
                    (currKeyWord->keycode == expectedKeyCode || expectedKeyCode == -1)) || (currKeyWord && expectedKeyCode == -1 && flags == SEPERATOR_EXPECTED))
        {
            switch (currKeyWord->keycode) {
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
                case 13:
                    fprintf(wPtr, "Keyword from\n");
                    break;
                default:
                    fprintf(stderr, "Unexpected error! Exiting\n");
                    exit(-1);
            }
            flags = currKeyWord->flagsForNextWord;
            expectedKeyCode = currKeyWord->expectedKeycode;
        } else{
            if(isStringConstant(currWord, tracker) && ((flags & STRING_EXPECTED) == STRING_EXPECTED)){
                fprintf(wPtr, "StringConstant %s\n", currWord);
                if(flags == OUT_LIST){
                    flags = SEPERATOR_EXPECTED;
                } else flags = NOP;
            }
            else if(isIntConstant(currWord) && ((flags & INT_EXPECTED) == INT_EXPECTED)){
                fprintf(wPtr, "IntConstant %s\n", currWord);
                if(flags == OUT_LIST){
                    flags = SEPERATOR_EXPECTED;
                } else flags = NOP;
            }
            else if(isVariable(currWord) && ((flags & IDENTIFIER_EXPECTED) == IDENTIFIER_EXPECTED)){
                fprintf(wPtr, "Identifier %s\n", currWord);
                if(flags == OUT_LIST){
                    flags = SEPERATOR_EXPECTED;
                } else flags = NOP;
            }
            else err("\nUnrecognized character \"%s\", at line %d\n", currWord, getLine(tracker), &flags, &expectedKeyCode, fPtr);
        }
    }
}
