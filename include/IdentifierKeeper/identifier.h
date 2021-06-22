//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_IDENTIFIER_H
#define BIGADD_IDENTIFIER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

// IdentifierKeeper
/*
 * Keeps all declared Identifiers and its values
 * It uses Linked List as Structure
 * Identifier:
 *  - name: Identifier name.
 *  - val: Identifiers' value (not used yet)
 *  - next: next Identifier
 * IdentifierKeeper:
 *  - root: root of Linked List
 *  - size: size of list
 */

typedef struct identifierNode {
    char *name;
    BigInt* value;
    struct identifierNode *next;
} Identifier;

typedef struct identifierKeeper {
    unsigned int size;
    Identifier *root;
} IdentifierKeeper;

bool isIdentifierDeclared(char *identifierName, IdentifierKeeper *keeper);

bool declareIdentifier(char *identifierName, IdentifierKeeper *keeper);

BigInt * getIdentifierData(char *identifierName, IdentifierKeeper *keeper);

IdentifierKeeper *createIdentifierKeeper();

void freeIdentifierKeeper(IdentifierKeeper *identifierKeeper);

#endif //BIGADD_IDENTIFIER_H
