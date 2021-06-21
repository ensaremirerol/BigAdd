//
// Created by ensar on 6/12/2021.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#define DECIMAL_SEP 10
#define NODE_MAX_VAL 10000000000
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct bigintNode{
    long long number;
    struct bigintNode* next;
    struct bigintNode* prev;
}BigIntNode;

typedef struct bigIntStruct{
    bool isNegative;
    BigIntNode* root;
    unsigned long long size;
}BigInt;


void addBigInt(BigInt* dest, BigInt* number);

void subBigInt(BigInt* dest, BigInt* number);

void tidyBigInt(BigInt* number);

int compare(BigInt* num1, BigInt* num2);

int compareAbsVal(BigInt* num1, BigInt* num2);

int _compareNode(BigIntNode *node1, BigIntNode *node2);

BigInt *copyBigInt(BigInt *number);

BigInt *strtobigInt(char* str);

void printBigInt(BigInt* number);

void _printbigIntNode(BigIntNode* node);

void freeBigInt(BigInt* number);

void freeBigIntNode(BigIntNode* node);

char digitCount(long long num);

#endif //BIGINT_BIGINT_H
