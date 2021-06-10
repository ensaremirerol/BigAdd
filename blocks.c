//
// Created by ensar on 5/26/2021.
//

#include "blocks.h"

void openBlock(BlockKeeper *blockKeeper, long int *loopCounter, unsigned int line, long int fPointer, bool isIntConstant) {
    Block *nBlock;
    nBlock = malloc(sizeof(Block));
    nBlock->lineStarted = line;
    nBlock->fPointer = fPointer;
    nBlock->loopCounter = loopCounter;
    nBlock->nests = NULL;
    nBlock->isIntConstant = isIntConstant;
    if (blockKeeper->totalBlocks == 0) blockKeeper->root = nBlock;
    else {
        Block *curr = blockKeeper->root;
        for (int i = 0; i < blockKeeper->totalBlocks - 1; i++) curr = curr->nests;
        curr->nests = nBlock;
    }
    blockKeeper->totalBlocks++;
}

Block* getBlock(BlockKeeper* blockKeeper){
    if (blockKeeper->totalBlocks == 0) return NULL;
    Block *curr = blockKeeper->root;
    if (blockKeeper->totalBlocks == 1) {
        return curr;
    } else {
        for (int i = 0; i < blockKeeper->totalBlocks - 1; i++) curr = curr->nests;
        return curr;
    }
}

bool closeBlock(BlockKeeper *blockKeeper) {
    if (blockKeeper->totalBlocks == 0) return false;
    Block *curr = blockKeeper->root;
    if (blockKeeper->totalBlocks == 1) {
        if(curr->isIntConstant) free(curr->loopCounter);
        free(curr);
        blockKeeper->root = NULL;
    } else {
        for (int i = 0; i < blockKeeper->totalBlocks - 2; i++) curr = curr->nests;
        if(curr->nests->isIntConstant) free(curr->nests->loopCounter);
        free(curr->nests);
        curr->nests = NULL;
    }
    blockKeeper->totalBlocks--;
    return true;
}

unsigned int closeBlockAndGetLine(BlockKeeper *blockKeeper) {
    if (blockKeeper->totalBlocks == 0) return -1;
    Block *curr = blockKeeper->root;
    unsigned int retVal;

    if (blockKeeper->totalBlocks == 1) {
        retVal = curr->lineStarted;
        free(curr);
        blockKeeper->root = NULL;
    } else {
        for (int i = 0; i < blockKeeper->totalBlocks - 2; i++) curr = curr->nests;
        retVal = curr->nests->lineStarted;
        free(curr->nests);
        curr->nests = NULL;
    }
    blockKeeper->totalBlocks--;
    return retVal;
}

BlockKeeper *createBlockKeeper() {
    BlockKeeper *blockKeeper;
    blockKeeper = malloc(sizeof(BlockKeeper));
    blockKeeper->totalBlocks = 0;
    blockKeeper->root = NULL;
    return blockKeeper;
}

void freeBlockKeeper(BlockKeeper *blockKeeper) {
    Block *curr = blockKeeper->root;
    Block *temp;
    while (curr && curr->nests) {
        temp = curr;
        curr = curr->nests;
        free(temp);
    }
    if (curr) free(curr);
    free(blockKeeper);
}
