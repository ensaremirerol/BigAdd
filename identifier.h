//
// Created by ensar on 5/26/2021.
//

#ifndef LEXICAL_WIN_IDENTIFIER_H
#define LEXICAL_WIN_IDENTIFIER_H
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
typedef struct identifierNode{
    char* name;
    int val;
    struct identifierNode* next;
}Identifier;

typedef struct identifierKeeper{
    unsigned int size;
    Identifier *root;
} IdentifierKeeper;

bool isIdentifierDeclared(char* identifierName, IdentifierKeeper* keeper){
    Identifier *curr = keeper->root;
    while (curr){
        if(strcmp(identifierName, curr->name) == 0) return true;
        curr = curr->next;
    }
    return false;
}
bool declareIdentifier(char* identifierName, IdentifierKeeper* keeper){
    if(isIdentifierDeclared(identifierName, keeper)) return false;
    Identifier *nIdentifier;
    nIdentifier = malloc(sizeof(Identifier));
    nIdentifier->name = malloc(strlen(identifierName) + 1);
    strcpy(nIdentifier->name, identifierName);
    nIdentifier->val = 0;
    nIdentifier->next = NULL;
    if(keeper->size == 0) keeper->root = nIdentifier;
    else{
        Identifier *curr = keeper->root;
        for (int i = 0; i < keeper->size-1; i++) curr = curr->next;
        curr->next = nIdentifier;
    }
    keeper->size++;
    return true;
}

IdentifierKeeper *createIdentifierKeeper(){
    IdentifierKeeper *keeper;
    keeper = malloc(sizeof (IdentifierKeeper));
    keeper->root = NULL;
    keeper->size = 0;
    return keeper;
}

void freeIdentifierKeeper(IdentifierKeeper* identifierKeeper){
    Identifier *curr = identifierKeeper->root;
    Identifier *temp;
    while (curr && curr->next){
        temp = curr;
        curr = curr->next;
        free(temp->name);
        free(temp);
    }
    if(curr){
        free(curr->name);
        free(curr);
    }
    free(identifierKeeper);
}
#endif //LEXICAL_WIN_IDENTIFIER_H
