//
// Created by ensar on 6/10/2021.
//

#ifndef BIGADD_ERRHANDLE_H
#define BIGADD_ERRHANDLE_H
#include <stdio.h>
#include "../Word/word.h"
#include "../KeyWord/keyword.h"
#include "../Blocks/blocks.h"

void err(Word *word, TokenType currentToken, KeyWord *root, Keycode expectedKeycode, unsigned char flag, unsigned int line);
void checkBlocks(BlockKeeper *blockKeeper);

#endif //BIGADD_ERRHANDLE_H
