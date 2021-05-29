//
// Created by ensar on 5/24/2021.
//

#ifndef LEXICAL_KEYWORD_H
#define LEXICAL_KEYWORD_H

#define LINE_ENDED           0b00000001
#define STRING_EXPECTED      0b00000010
#define INT_EXPECTED         0b00000100
#define IDENTIFIER_USE       0b00001000
#define IDENTIFIER_DECLARE   0b00100000
#define BLOCK_EXPECTED       0b01000001
#define NOP                  0b10000000
#define IDENTIFIER_EXPECTED  0b00101000
#define KEYWORD_EXPECTED     0b11000001
#define INT_VAL              0b00001100
#define OUT_LIST             0b00001110

typedef struct keyWordStruct{
    char* keyWord;
    char expectedKeycode;
    char keycode;
    unsigned char flagsForKeyword;
    unsigned char flagsForNextWord;
    struct keyWordStruct *next;
}KeyWord;

KeyWord *addKeyWord(char* keyWord, KeyWord* prev, char keycode, char expectedKeyCode, unsigned char flagsForKeyWord,
                       unsigned char flagsForNextKeyWord){
    KeyWord *nKeyWord;
    nKeyWord = (KeyWord *) malloc(sizeof(KeyWord));
    nKeyWord->keyWord = keyWord;
    nKeyWord->next = NULL;
    nKeyWord->keycode = keycode;
    nKeyWord->expectedKeycode = expectedKeyCode;
    nKeyWord->flagsForKeyword = flagsForKeyWord;
    nKeyWord->flagsForNextWord = flagsForNextKeyWord;

    prev->next = nKeyWord;

    return nKeyWord;
}

KeyWord *createKeyWordLinkedList() {
    KeyWord *head;
    KeyWord *curr;
    head = malloc(sizeof(KeyWord));
    head->keyWord = "int";
    head->keycode = 0;
    head->expectedKeycode = 11;
    head->flagsForKeyword = LINE_ENDED;
    head->flagsForNextWord = IDENTIFIER_DECLARE;
    // int 0
    curr = head;
    // move 1
    curr = addKeyWord("move", curr, 1, 10, LINE_ENDED, INT_VAL);
    // add 2
    curr = addKeyWord("add", curr, 2, 10, LINE_ENDED, INT_VAL);
    // sub 3
    curr = addKeyWord("sub", curr, 3, 13, LINE_ENDED,INT_VAL);
    // out 4
    curr = addKeyWord("out", curr, 4, 12, LINE_ENDED, OUT_LIST);
    // loop 5
    curr = addKeyWord("loop", curr, 5, 8, LINE_ENDED,INT_VAL);
    // [ 6
    curr = addKeyWord("[", curr, 6, -1, BLOCK_EXPECTED, LINE_ENDED);
    // ] 7
    curr = addKeyWord("]", curr, 7, -1, LINE_ENDED, LINE_ENDED);
    // times 8
    curr = addKeyWord("times", curr, 8, -1, NOP, BLOCK_EXPECTED);
    // newline 9
    curr = addKeyWord("newline", curr, 9, 12, OUT_LIST, NOP);
    // to 10
    curr = addKeyWord("to", curr, 10, 11, NOP, IDENTIFIER_USE);
    // . 11
    curr = addKeyWord(".", curr, 11, -1, NOP, LINE_ENDED);
    // , 12
    curr = addKeyWord(",", curr, 12, 12, NOP, OUT_LIST);
    // from 13
    addKeyWord("from", curr, 13, 11 , NOP, IDENTIFIER_USE);

    return head;
}

KeyWord *getKeyWord(char *keyWord, KeyWord *keyWordRoot){
    KeyWord *curr = keyWordRoot;
    char i = 0;
    while (curr != NULL) {
        if (strcmp(curr->keyWord, keyWord) == 0) return curr;
        curr = curr->next;
        i++;
    }
    return NULL;
}

KeyWord *getKeyWordbyIndex(char keyCode, KeyWord *keyWordRoot){
    KeyWord *curr = keyWordRoot;
    char i = 0;
    while (curr != NULL) {
        if (curr->keycode == keyCode) return curr;
        curr = curr->next;
        i++;
    }
    return NULL;
}

void freeKeyWordLinkedList(KeyWord* root){
    KeyWord *temp;
    while (root && root->next){
        temp = root;
        root = root->next;
        free(temp);
    }
    if(root){
        free(root);
    }
}

bool isIntConstant(char *str) {
    if (!((str[0] == '-' && strlen(str) <= 101) || ((str[0] >= '0' && str[0] <= '9') && strlen(str) <= 100))) return false;
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

bool isStringConstant(char *str, LineTracker *tracker) {
    if (str[0] == LEXEME_STRING) {
        if (str[strlen(str) - 1] == LEXEME_STRING) return true;
        fprintf(stderr, "String constant does not close at line: %d", getLine(tracker));
        exit(-1);
    }
    return false;
}

#endif //LEXICAL_KEYWORD_H
