//
// Created by ensar on 6/8/2021.
//

#include "../../include/KeyWord/keyword.h"

KeyWord *addKeyWord(char *keyWord, KeyWord *prev, Keycode keycode, Keycode expectedKeyCode, unsigned char flagsForKeyWord,
                    unsigned char flagsForNextKeyWord, void (*operationFunc)(Variable* stack, IdentifierKeeper *identifierKeeper)) {
    KeyWord *nKeyWord;
    nKeyWord = (KeyWord *) malloc(sizeof(KeyWord));
    nKeyWord->keyWord = keyWord;
    nKeyWord->next = NULL;
    nKeyWord->keycode = keycode;
    nKeyWord->expectedKeycode = expectedKeyCode;
    nKeyWord->flagsForKeyword = flagsForKeyWord;
    nKeyWord->flagsForNextWord = flagsForNextKeyWord;
    nKeyWord->operationFunc = operationFunc;

    prev->next = nKeyWord;

    return nKeyWord;
}

KeyWord *createKeyWordLinkedList() {
    KeyWord *head;
    KeyWord *curr;
    head = malloc(sizeof(KeyWord));
    head->keyWord = "int";
    head->keycode = bInt;
    head->expectedKeycode = bEOL;
    head->flagsForKeyword = LINE_ENDED;
    head->flagsForNextWord = IDENTIFIER_DECLARE;
    head->operationFunc = identifier;
    // int 0
    curr = head;
    // move 1
    curr = addKeyWord("move", curr, bMove, bTo, LINE_ENDED, INT_VAL, move);
    // add 2
    curr = addKeyWord("add", curr, bAdd, bTo, LINE_ENDED, INT_VAL, add);
    // sub 3
    curr = addKeyWord("sub", curr, bSub, bFrom, LINE_ENDED, INT_VAL, sub);
    // out 4
    curr = addKeyWord("out", curr, bOut, bSeparator, LINE_ENDED, OUT_LIST, out);
    // loop 5
    curr = addKeyWord("loop", curr, bLoop, bTimes, LINE_ENDED, INT_VAL, NULL);
    // [ 6
    curr = addKeyWord("[", curr, bOpenBlock, bNop, BLOCK_EXPECTED, LINE_ENDED, NULL);
    // ] 7
    curr = addKeyWord("]", curr, bCloseBlock, bNop, LINE_ENDED, LINE_ENDED, NULL);
    // times 8
    curr = addKeyWord("times", curr, bTimes, bNop, NOP, BLOCK_EXPECTED, NULL);
    // newline 9
    curr = addKeyWord("newline", curr, bNewline, bSeparator, OUT_LIST, NOP, NULL);
    // to 10
    curr = addKeyWord("to", curr, bTo, bEOL, NOP, IDENTIFIER_USE, NULL);
    // . 11
    curr = addKeyWord(".", curr, bEOL, bNop, NOP, LINE_ENDED, NULL);
    // , 12
    curr = addKeyWord(",", curr, bSeparator, bSeparator, NOP, OUT_LIST, NULL);
    // from 13
    addKeyWord("from", curr, bFrom, bEOL, NOP, IDENTIFIER_USE, NULL);

    return head;
}

KeyWord *getKeyWord(char *keyWord, KeyWord *keyWordRoot) {
    KeyWord *curr = keyWordRoot;
    char i = 0;
    while (curr != NULL) {
        if (strcmp(curr->keyWord, keyWord) == 0) return curr;
        curr = curr->next;
        i++;
    }
    return NULL;
}

KeyWord *getKeyWordByKeyCode(Keycode keyCode, KeyWord *keyWordRoot){
    KeyWord *curr = keyWordRoot;
    char i = 0;
    while (curr != NULL) {
        if (curr->keycode == keyCode) return curr;
        curr = curr->next;
        i++;
    }
    return NULL;
}

void freeKeyWordLinkedList(KeyWord *root) {
    KeyWord *temp;
    while (root && root->next) {
        temp = root;
        root = root->next;
        free(temp);
    }
    if (root) {
        free(root);
    }
}

bool isIntConstant(char *str) {
    if (!((str[0] == '-' && strlen(str) <= 101) || ((str[0] >= '0' && str[0] <= '9') && strlen(str) <= 100)))
        return false;
    for (int i = 1; i < strlen(str); i++) if (!(str[i] >= '0' && str[i] <= '9')) return false;
    return true;
}

bool isIdentifier(char *str) {
    if (!(((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] < 'Z')) && strlen(str) <= 20)) return false;
    for (int i = 0; i < strlen(str); i++)
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            return false;
    return true;
}

bool isStringConstant(char *str, const unsigned int *line) {
    if (str[0] == LEXEME_STRING) {
        if (str[strlen(str) - 1] == LEXEME_STRING) return true;
        fprintf(stdout, "String constant does not close at line: %d\n", *line);
    }
    return false;
}

void identifier(Variable* stack, IdentifierKeeper* identifierKeeper){
    char* str = (char*) stack->data;
    declareIdentifier(str, identifierKeeper);
}

void move(Variable* stack, IdentifierKeeper* identifierKeeper){
    Variable *curr = stack;
    BigInt *val;
    if(curr->dataType == dIdentifier) val = getIdentifierData((char*) curr->data, identifierKeeper);
    else val = ((BigInt *) curr->data);
    curr = curr->next;
    BigInt * identifierVal = getIdentifierData((char*) curr->data, identifierKeeper);
    freeBigIntNode(identifierVal->root);
    BigInt *new = copyBigInt(val);
    identifierVal->root = new->root;
    identifierVal->isNegative = new->isNegative;
    identifierVal->size = new->size;
    free(new);
}

void add(Variable* stack, IdentifierKeeper* identifierKeeper){
    Variable *curr = stack;
    BigInt *val;
    if(curr->dataType == dIdentifier) val = getIdentifierData((char*) curr->data, identifierKeeper);
    else val = ((BigInt*) curr->data);
    curr = curr->next;
    BigInt *identifierVal = getIdentifierData((char*) curr->data, identifierKeeper);
    addBigInt(identifierVal, val);
}

void sub(Variable* stack, IdentifierKeeper* identifierKeeper){
    Variable *curr = stack;
    BigInt *val;
    if(curr->dataType == dIdentifier) val = getIdentifierData((char*) curr->data, identifierKeeper);
    else val = ((BigInt*) curr->data);
    curr = curr->next;
    BigInt *identifierVal = getIdentifierData((char*) curr->data, identifierKeeper);
    subBigInt(identifierVal, val);
}

void out(Variable* stack, IdentifierKeeper* identifierKeeper){
    Variable *curr = stack;
    while(curr){
        switch (curr->dataType) {
            case dIdentifier:
                printBigInt(getIdentifierData((char*) curr->data, identifierKeeper));
                break;
            case dStringConstant:
                if(((char*) curr->data)[0] == '\n') printf("\n");
                for (int i = 1; i < strlen((char*) curr->data)-1; ++i) {
                    printf("%c", ((char*) curr->data)[i]);
                }
                break;
            case dIntConstant:
                printf("%lld", *((long long int*) curr->data));
                break;
        }
        curr = curr->next;
    }
    fflush(stdout);
}

