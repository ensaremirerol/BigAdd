//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_PARSER_H
#define BIGADD_PARSER_H

#include "blocks.h"
#include "parser.h"
#include "lxanalyzer.h"
#include "keyword.h"
#include "identifier.h"
#include "variablestack.h"

void parser(LexicalData* data);

void loop(Variable* stack, IdentifierKeeper* identifierKeeper, LexicalData* data, BlockKeeper* blockKeeper);

#endif //BIGADD_PARSER_H
