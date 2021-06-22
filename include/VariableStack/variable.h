//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_VARIABLE_H
#define BIGADD_VARIABLE_H
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

typedef enum dataType {
    dIdentifier, dIntConstant, dStringConstant
}DataType;

typedef struct variableStack{
    DataType dataType;
    void* data;
    struct variableStack *next;
}Variable;

Variable* addVariable(Variable* curr, void* data, DataType type);

void freeVariableStack(Variable* curr);

#endif //BIGADD_VARIABLE_H
