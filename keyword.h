//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_KEYWORD_H
#define BIGADD_KEYWORD_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "variable.h"
#include "identifier.h"

#define LINE_ENDED           0b00000001
#define STRING_EXPECTED      0b00000010
#define INT_EXPECTED         0b00000100
#define IDENTIFIER_USE       0b00001000
#define IDENTIFIER_DECLARE   0b00100000
#define BLOCK_EXPECTED       0b01000001
#define NOP                  0b10000000
#define IDENTIFIER_EXPECTED  0b00101000
#define KEYWORD_EXPECTED     0b11000001
#define INT_VAL              0b00001100
#define OUT_LIST             0b00001110

#define LEXEME_STRING '"'

// KeyWord
/*
 * Keeps all keywords.
 * Keyword:
 *  - keyword: keyword. (as char array)
 *  - keycode: its' code.
 *  - expectedKeycode: Expected keycode after this keyword.
 *  - flagsForKeyword: Expected flag for the use of this keyWord
 *  - flagsForNextWord: Flag for next expected "word". (It could be anything (Identifier, String, Int, ...))
 *  - next: next Keyword.
 */

typedef enum keycode {bInt, bMove, bAdd, bSub, bOut, bLoop, bOpenBlock, bCloseBlock, bTimes, bNewline, bTo, bEOL, bSeparator,
    bFrom, bNop} Keycode;

typedef enum tokentype {bKeyword, bIntConstant, bStringConstant, bIdentifier,  bEOF, bError} TokenType;

typedef struct keyWordStruct {
    char *keyWord;
    Keycode expectedKeycode;
    Keycode keycode;
    unsigned char flagsForKeyword;
    unsigned char flagsForNextWord;
    void (*operationFunc)(Variable* stack, IdentifierKeeper* identifierKeeper);
    struct keyWordStruct *next;
} KeyWord;

KeyWord *addKeyWord(char *keyWord, KeyWord *prev, Keycode keycode, Keycode expectedKeyCode, unsigned char flagsForKeyWord,
                    unsigned char flagsForNextKeyWord, void (*operationFunc)());

KeyWord *createKeyWordLinkedList();

KeyWord *getKeyWord(char *keyWord, KeyWord *keyWordRoot);

KeyWord *getKeyWordByIndex(char keyCode, KeyWord *keyWordRoot);

void freeKeyWordLinkedList(KeyWord *root);

bool isIntConstant(char *str);

bool isIdentifier(char *str);

bool isStringConstant(char *str, const unsigned int *line);

void identifier(Variable* stack, IdentifierKeeper* identifierKeeper);

void move(Variable* stack, IdentifierKeeper* identifierKeeper);

void add(Variable* stack, IdentifierKeeper* identifierKeeper);

void sub(Variable* stack, IdentifierKeeper* identifierKeeper);

void out(Variable* stack, IdentifierKeeper* identifierKeeper);

#endif //BIGADD_KEYWORD_H
