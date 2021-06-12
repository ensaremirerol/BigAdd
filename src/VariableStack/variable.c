//
// Created by ensar on 6/8/2021.
//

#include "../../include/VariableStack/variable.h"

Variable* addVariable(Variable* curr, void* data, DataType type){
    Variable *nVar = malloc(sizeof (Variable));
    nVar->dataType = type;
    switch (type) {
        case dStringConstant:
        case dIdentifier:{
            char* str = malloc(strlen((char*) data) + 1);
            strcpy(str, (char*) data);
            nVar->data = str;
            break;
        }
        case dIntConstant:{
            long long int *val = malloc(sizeof (long long int));
            *val = *((long long int*) data);
            nVar->data = val;
            break;
        }
        default:{
            // TODO: ERR
            exit(-1);
        }
    }
    nVar->next = NULL;
    if(curr){
        Variable *tmp = curr;
        while (tmp->next) tmp = tmp->next;
        tmp->next = nVar;
        return curr;
    }
    return nVar;
}

void freeVariableStack(Variable* curr){
    Variable *temp;
    while(curr){
        free(curr->data);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}