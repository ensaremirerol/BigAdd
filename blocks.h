//
// Created by ensar on 5/26/2021.
//

#ifndef LEXICAL_WIN_BLOCKS_H
#define LEXICAL_WIN_BLOCKS_H

#include <stdlib.h>
#include <stdbool.h>

// BlockKeeper
/*
 * Keeps all all opened blocks and where it opened
 * It uses Linked List as Structure
 * When two blocks are nested, nested block linked inside first block
 * Block:
 *  - lineStarted: Blocks' start line.
 *  - nests: Points nested block.
 * BlockKeeper:
 *  - root: Root of linked list.
 *  - totalBlocks: Count of currently open blocks
 */

typedef struct blockNode {
    int lineStarted;
    struct blockNode *nests;
} Block;

typedef struct blockKeeper {
    unsigned int totalBlocks;
    Block *root;
} BlockKeeper;

void openBlock(BlockKeeper *blockKeeper, int line) {
    Block *nBlock;
    nBlock = malloc(sizeof(Block));
    nBlock->lineStarted = line;
    nBlock->nests = NULL;
    if (blockKeeper->totalBlocks == 0) blockKeeper->root = nBlock;
    else {
        Block *curr = blockKeeper->root;
        for (int i = 0; i < blockKeeper->totalBlocks - 1; i++) curr = curr->nests;
        curr->nests = nBlock;
    }
    blockKeeper->totalBlocks++;
}

bool closeBlock(BlockKeeper *blockKeeper) {
    if (blockKeeper->totalBlocks == 0) return false;
    Block *curr = blockKeeper->root;
    if (blockKeeper->totalBlocks == 1) {
        free(curr);
        blockKeeper->root = NULL;
    } else {
        for (int i = 0; i < blockKeeper->totalBlocks - 2; i++) curr = curr->nests;
        free(curr->nests);
        curr->nests = NULL;
    }
    blockKeeper->totalBlocks--;
    return true;
}

int closeBlockAndGetLine(BlockKeeper *blockKeeper) {
    if (blockKeeper->totalBlocks == 0) return -1;
    Block *curr = blockKeeper->root;
    int retVal;

    if (blockKeeper->totalBlocks == 1) {
        retVal = curr->lineStarted;
        free(curr);
        blockKeeper->root = NULL;
    } else {
        for (int i = 0; i < blockKeeper->totalBlocks - 1; i++) curr = curr->nests;
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

#endif //LEXICAL_WIN_BLOCKS_H
