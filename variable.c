//
// Created by ensar on 6/8/2021.
//

#include "variable.h"

Variable* addVariable(Variable* curr, void* data, DataType type){
    Variable *nVar = malloc(sizeof (Variable));
    nVar->dataType = type;
    nVar->data = data;
    nVar->next = NULL;
    if(curr){
        Variable *tmp = curr;
        while (curr->next) tmp = curr = curr->next;
        curr->next = nVar;
        return curr;
    }
    return nVar;
}

void freeVariableStack(Variable* curr){
    Variable *temp;
    while(curr){
        if(curr->dataType != dIdentifier) free(curr->data);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}