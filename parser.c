//
// Created by ensar on 6/8/2021.
//

#include "parser.h"

void parser(LexicalData* data){

    unsigned char flag = LINE_ENDED;
    Keycode expectedKeycode = bNop;

    KeyWord *root;
    root = createKeyWordLinkedList();

    IdentifierKeeper *identifierKeeper;
    identifierKeeper = createIdentifierKeeper();

    BlockKeeper *blockKeeper;
    blockKeeper = createBlockKeeper();
    Block *currBlock;

    TokenType currToken;

    Variable *stack;

    void (*currOperation)(Variable *stack, IdentifierKeeper *identifierKeeper);

    while (true){
        currToken = lexicalAnalyzer(data, root);
        if(currToken == bEOF) break;
        if(currToken == bError){
            // TODO: Unrecognized token
            // TODO: ERR CODE
            exit(0);
        }
        if((flag & KEYWORD_EXPECTED) == 0){
            if(currToken == bKeyword){
                /*
                 * If data->currWord->word is a keyWord
                 * 1-) This is a Error
                 * 2-) KeyWord is "newline"
                 * "newline" is a Key Word but lexical analyzer treats as a not keyword because of
                 * flags. "newline" KeyWord only can come after "out" keyword (flags==OUT_LIST)
                 */
                // keycode 9 is keycode of "newline"
                if (!(data->currKeyword->keycode == bNewline && flag == OUT_LIST)) {
                    // TODO: Unexpected keyword!
                    // TODO: ERR CODE
                    exit(0);
                }
                flag = data->currKeyword->flagsForNextWord;
                expectedKeycode = data->currKeyword->expectedKeycode;
                stack = addVariable(stack, "\n", dStringConstant);
                continue;
            }

            else if(currToken == bIdentifier && (flag & IDENTIFIER_EXPECTED) != 0){
                if ((flag & IDENTIFIER_DECLARE) == IDENTIFIER_DECLARE) {
                    // Declare identifier if not. If it's already declared give error
                    if (isIdentifierDeclared(data->currWord->word, identifierKeeper)) {
                        // TODO: Identifier has already declared!
                        // TODO: ERR CODE
                        exit(0);
                    }
                }
                // Are we using a identifier?
                else if ((flag & IDENTIFIER_USE) == IDENTIFIER_USE) {
                    // Has identifier declared?
                    if (!isIdentifierDeclared(data->currWord->word, identifierKeeper)) {
                        // TODO: Identifier has not declared!
                        // TODO: ERR CODE
                        exit(0);
                    }
                }
            }

            else if (currToken == bIntConstant && (flag & INT_EXPECTED) == INT_EXPECTED) {
                long int val = atol(data->currWord->word);
                stack = addVariable(stack, &val, dStringConstant);
            }
            // Is data->currWord->word a String and is it expected?
            else if (currToken == bStringConstant && (flag & STRING_EXPECTED) == STRING_EXPECTED){
                stack = addVariable(stack, data->currWord->word, dStringConstant);
            }

            else{
                // TODO: Unrecognized Error!
                // TODO: ERR CODE
                exit(0);
            }

            flag = NOP;
        }

        else if(currToken == bKeyword && (flag & KEYWORD_EXPECTED) != 0){
            /*
             * If
             * 1-) Keywords' flag and keycode matches current flag and expected keycode
             * 2-) Flags' LINE_ENDED BIT is 1 and expected keycode is -1
             * 3-) Flag is NOP, expected keycode is 12(',') and current keywords' keycode is 11('.')
             *     (Exception for "out")
             */
            if (((flag & data->currKeyword->flagsForKeyword) == data->currKeyword->flagsForKeyword &&
                 expectedKeycode == data->currKeyword->keycode) || ((flag & LINE_ENDED) != 0 && expectedKeycode == bNop) ||
                (flag == NOP && expectedKeycode == bSeparator && data->currKeyword->keycode == bEOL)){
                switch (data->currKeyword->keycode) {
                    case bEOL:
                        currOperation(stack, identifierKeeper);
                        currOperation = NULL;
                        freeVariableStack(stack);
                        break;
                    case bOpenBlock:
                        // Are we expecting a block?
                        if ((flag & BLOCK_EXPECTED) == BLOCK_EXPECTED) {
                            loop(stack, identifierKeeper, data, blockKeeper);
                            currBlock = getBlock(blockKeeper);
                        }
                        else{
                            // TODO: Unexpected block open!
                            // TODO: ERR CODE
                            exit(0);
                        }
                        break;
                    case bCloseBlock:
                        // NOTE: Upper if block should check for semantics
                        // Is/Are there any block/s?
                        if(*(currBlock->loopCounter) != 0){
                            fseek(data->fPtr, currBlock->fPointer, SEEK_SET);
                            data->currLine = currBlock->lineStarted;
                            *(currBlock->loopCounter) -= 1;
                        }
                        else if (closeBlock(blockKeeper))
                            currBlock = getBlock(blockKeeper);
                        else{
                            // TODO: Unexpected block close!
                            // TODO: ERR CODE
                            exit(0);
                        }
                        break;
                    default: break;
                }
                if(data->currKeyword->operationFunc){
                    if(currOperation){
                        // TODO: Unexpected Keyword!
                        // TODO: ERR CODE
                        exit(0);
                    }
                    currOperation = data->currKeyword->operationFunc;
                }

                flag = data->currKeyword->flagsForNextWord;
                expectedKeycode = data->currKeyword->expectedKeycode;
            }
        }

    }
}

void loop(Variable* stack, IdentifierKeeper* identifierKeeper, LexicalData* data, BlockKeeper* blockKeeper){
    Variable *curr = stack;
    long int *val;
    if(curr->dataType == dIdentifier)
        val = getIdentifierData((char*) curr->data, identifierKeeper);
    else
        *val = *((long int*) curr->data);
    openBlock(blockKeeper, val, data->currLine, ftell(data->fPtr));
}
