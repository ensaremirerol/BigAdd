//
// Created by ensar on 6/10/2021.
//

#include "../../include/ErrorHandle/errhandle.h"

void err(Word *word, TokenType currentToken, KeyWord *root, Keycode expectedKeycode, unsigned char flag, unsigned int line){
    if((flag & KEYWORD_EXPECTED) == 0){
        if(currentToken == bKeyword){
            switch (flag) {
                case INT_VAL:
                    fprintf(stderr, "Expected declared identifier or Int Constant but found keyword \"%s\" at line"
                            " %d\n", word->word, line);
                    break;
                case IDENTIFIER_USE:
                    fprintf(stderr, "Expected declared identifier but found keyword \"%s\" at line"
                            " %d\n", word->word, line);
                    break;
                case OUT_LIST:
                    fprintf(stderr, "Expected declared identifier, Int Constant or String but found keyword \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                case INT_EXPECTED:
                    fprintf(stderr, "Expected Int Constant but found keyword \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                case IDENTIFIER_DECLARE:
                    fprintf(stderr, "Expected not declared identifier but found keyword \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                default:
                    fprintf(stderr, "Not recognized error! Found keyword \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
            }
        }
        else if (currentToken == bError){
            switch (flag) {
                case INT_VAL:
                    fprintf(stderr, "Expected declared identifier or Int Constant but found \"%s\" at line"
                            " %d\n", word->word, line);
                    break;
                case IDENTIFIER_USE:
                    fprintf(stderr, "Expected declared identifier but found \"%s\" at line"
                            " %d\n", word->word, line);
                    break;
                case OUT_LIST:
                    fprintf(stderr, "Expected declared identifier, Int Constant or String but found \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                case INT_EXPECTED:
                    fprintf(stderr, "Expected Int Constant but found \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                case IDENTIFIER_DECLARE:
                    fprintf(stderr, "Expected not declared identifier but found \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
                default:
                    fprintf(stderr, "Not recognized error! Found \"%s\", at line"
                                    " %d\n", word->word, line);
                    break;
            }
        }
        else{
            switch (flag) {
                case INT_VAL:
                    fprintf(stderr, "Expected declared identifier or Int Constant but found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
                case IDENTIFIER_USE:
                    fprintf(stderr, "Expected declared identifier but found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
                case OUT_LIST:
                    fprintf(stderr, "Expected declared identifier, Int Constant or String but found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
                case INT_EXPECTED:
                    fprintf(stderr, "Expected Int Constant but found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
                case IDENTIFIER_DECLARE:
                    fprintf(stderr, "Expected not declared identifier but found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
                default:
                    fprintf(stderr, "Not recognized error! Found \"%s\" at line"
                                    " %d\n", word->word, line);
                    break;
            }
        }
    }
    else if((flag & KEYWORD_EXPECTED) != 0){
        if(expectedKeycode != bNop){
            KeyWord *expected = getKeyWordByKeyCode(expectedKeycode, root);
            if(currentToken == bKeyword){
                fprintf(stderr, "Expected keyword \"%s\" but found keyword \"%s\" at line"
                                " %d\n", expected->keyWord, word->word, line);
            }
            else{
                fprintf(stderr, "Expected keyword \"%s\" but found \"%s\" at line"
                                " %d\n", expected->keyWord, word->word, line);
            }
        }
        else{
            if(currentToken == bKeyword){
                fprintf(stderr, "Keyword \"%s\" cannot be used start of the line! at line"
                                " %d\n", word->word, line);
            }
            else{
                fprintf(stderr, "Expected keyword but found \"%s\" at line"
                                " %d\n", word->word, line);
            }
        }
    }
    else
        fprintf(stderr, "Not recognized error! Error -> \"%s\" at line"
                        " %d\n", word->word, line);

    exit(-1);
}

void checkBlocks(BlockKeeper *blockKeeper) {
    while (blockKeeper->totalBlocks != 0) {
        fprintf(stderr, "Block(line, %d) left open!\n", closeBlockAndGetLine(blockKeeper));
    }
}