//
// Created by ensar on 6/8/2021.
//

#include "../../include/IdentifierKeeper/identifier.h"

bool isIdentifierDeclared(char *identifierName, IdentifierKeeper *keeper) {
    Identifier *curr = keeper->root;
    while (curr) {
        if (strcmp(identifierName, curr->name) == 0) return true;
        curr = curr->next;
    }
    return false;
}

bool declareIdentifier(char *identifierName, IdentifierKeeper *keeper) {
    if (isIdentifierDeclared(identifierName, keeper)) return false;
    Identifier *nIdentifier;
    nIdentifier = malloc(sizeof(Identifier));
    nIdentifier->name = malloc(strlen(identifierName) + 1);
    strcpy(nIdentifier->name, identifierName);
    nIdentifier->val = 0;
    nIdentifier->next = NULL;
    if (keeper->size == 0) keeper->root = nIdentifier;
    else {
        Identifier *curr = keeper->root;
        for (int i = 0; i < keeper->size - 1; i++) curr = curr->next;
        curr->next = nIdentifier;
    }
    keeper->size++;
    return true;
}

long int* getIdentifierData(char *identifierName, IdentifierKeeper *keeper){
    Identifier *curr = keeper->root;
    while (curr) {
        if (strcmp(identifierName, curr->name) == 0) return &curr->val;
        curr = curr->next;
    }
    return NULL;
}

IdentifierKeeper *createIdentifierKeeper() {
    IdentifierKeeper *keeper;
    keeper = malloc(sizeof(IdentifierKeeper));
    keeper->root = NULL;
    keeper->size = 0;
    return keeper;
}

void freeIdentifierKeeper(IdentifierKeeper *identifierKeeper) {
    Identifier *curr = identifierKeeper->root;
    Identifier *temp;
    while (curr && curr->next) {
        temp = curr;
        curr = curr->next;
        free(temp->name);
        free(temp);
    }
    if (curr) {
        free(curr->name);
        free(curr);
    }
    free(identifierKeeper);
}
