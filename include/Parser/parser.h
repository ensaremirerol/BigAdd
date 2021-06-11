//
// Created by ensar on 6/8/2021.
//

#ifndef BIGADD_PARSER_H
#define BIGADD_PARSER_H

#include "../Blocks/blocks.h"
#include "parser.h"
#include "../LexicalAnalyzer/lxanalyzer.h"
#include "../KeyWord/keyword.h"
#include "../IdentifierKeeper/identifier.h"
#include "../VariableStack/variable.h"
#include "../ErrorHandle/errhandle.h"



void parser(LexicalData* data);

void loop(Variable* stack, IdentifierKeeper* identifierKeeper, LexicalData* data, BlockKeeper* blockKeeper, bool isShortHandLoop);

#endif //BIGADD_PARSER_H
