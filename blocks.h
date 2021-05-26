//
// Created by ensar on 5/26/2021.
//

#ifndef LEXICAL_WIN_BLOCKS_H
#define LEXICAL_WIN_BLOCKS_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct blockNode{
    int lineStarted;
    struct blockNode* nests;
}Block;

typedef struct blockKeeper{
    unsigned int totalBlocks;
    Block *root;
}BlockKeeper;

void openBlock(BlockKeeper* blockKeeper, int line){
    Block *nBlock;
    nBlock = malloc(sizeof(Identifier));
    nBlock->lineStarted = line;
    nBlock->nests = NULL;
    if(blockKeeper->totalBlocks == 0) blockKeeper->root = nBlock;
    else{
        Block *curr = blockKeeper->root;
        for (int i = 0; i < blockKeeper->totalBlocks-1; i++) curr = curr->nests;
        curr->nests = nBlock;
    }
    blockKeeper->totalBlocks++;
}

bool closeBlock(BlockKeeper* blockKeeper){
    if(blockKeeper->totalBlocks == 0) return false;
    Block *curr = blockKeeper->root;
    for (int i = 0; i < blockKeeper->totalBlocks-1; i++) curr = curr->nests;
    if(curr->nests){
        free(curr->nests);
        curr->nests = NULL;
    }
    else{
        free(curr);
        blockKeeper->root = NULL;
    }
    blockKeeper->totalBlocks--;
    return true;
}

int closeBlockAndGetLine(BlockKeeper* blockKeeper){
    if(blockKeeper->totalBlocks == 0) return -1;
    Block *curr = blockKeeper->root;
    int retVal;
    for (int i = 0; i < blockKeeper->totalBlocks-1; i++) curr = curr->nests;
    if(curr->nests){
        retVal = curr->nests->lineStarted;
        free(curr->nests);
        curr->nests = NULL;
    }
    else{
        retVal = curr->lineStarted;
        free(curr);
        blockKeeper->root = NULL;
    }
    blockKeeper->totalBlocks--;
    return retVal;
}

BlockKeeper* createBlockKeeper(){
    BlockKeeper *blockKeeper;
    blockKeeper = malloc(sizeof(BlockKeeper));
    blockKeeper->totalBlocks = 0;
    blockKeeper->root = NULL;
    return blockKeeper;
}
#endif //LEXICAL_WIN_BLOCKS_H
