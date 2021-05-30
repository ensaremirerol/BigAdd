//
// Created by ensar on 5/24/2021.
//
#include <stdio.h>
#include "fileio.h"
#include "keyword.h"
#include "blocks.h"

#ifndef LEXICAL_ERRHANDLE_H
#define LEXICAL_ERRHANDLE_H

// Resets lexical analyzer.
void resetToEOL(char *word, unsigned char *flag, char *expectedKeycode, FILE *fPtr, LineTracker *tracker) {
    *flag = LINE_ENDED;
    *expectedKeycode = -1;
    if (strcmp(word, ".") != 0) seekEOL(fPtr, tracker);
}

// Handles all errors
void err(char *word, KeyWord *root, char *expectedKeycode, unsigned char *flag, FILE *fPtr, LineTracker *tracker) {

    // If keyword expected
    if ((*flag & KEYWORD_EXPECTED) == 0) {
        if(getKeyWord(word, root)){
            switch (*flag) {
                case INT_VAL:
                    fprintf(stderr, "Expected declared identifier or Int Constant but found keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case IDENTIFIER_USE:
                    fprintf(stderr, "Expected declared identifier but found keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case OUT_LIST:
                    fprintf(stderr, "Expected declared identifier, Int Constant or String but found keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case INT_EXPECTED:
                    fprintf(stderr, "Expected Int Constant but found keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case IDENTIFIER_DECLARE:
                    fprintf(stderr, "Expected not declared identifier but found keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                default:
                    fprintf(stderr, "Not recognized error! Error -> keyword \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
            }
        }
        else
            switch (*flag) {
                case INT_VAL:
                    fprintf(stderr, "Expected declared identifier or Int Constant but found \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case IDENTIFIER_USE:
                    fprintf(stderr, "Expected declared identifier but found \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case OUT_LIST:
                    fprintf(stderr, "Expected declared identifier, Int Constant or String but found \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case INT_EXPECTED:
                    fprintf(stderr, "Expected Int Constant but found \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                case IDENTIFIER_DECLARE:
                    fprintf(stderr, "Expected not declared identifier but found \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
                default:
                    fprintf(stderr, "Not recognized error! Error -> \"%s\" at line"
                                    " %d\n", word, getLine(tracker));
                    break;
            }
    } else if ((*flag & KEYWORD_EXPECTED) != 0) {
        // If a keyCode is expected
        if (*expectedKeycode != -1) {
            KeyWord *expected = getKeyWordbyIndex(*expectedKeycode, root);
            fprintf(stderr, "Expected \"%s\" but found \"%s\" at line"
                            " %d\n", expected->keyWord, word, getLine(tracker));
        }
            // If not
        else
            fprintf(stderr, "Expected keyword but found \"%s\" at line"
                            " %d\n", word, getLine(tracker));

    }
        // Not recognized error!
    else
        fprintf(stderr, "Not recognized error! Error -> \"%s\" at line"
                        " %d\n", word, getLine(tracker));
    resetToEOL(word, flag, expectedKeycode, fPtr, tracker);
}

// Checks left open blocks
void checkBlocks(BlockKeeper *blockKeeper) {
    while (blockKeeper->totalBlocks != 0) {
        fprintf(stderr, "Block(line, %d) left open!\n", closeBlockAndGetLine(blockKeeper));
    }
}

#endif //LEXICAL_ERRHANDLE_H
