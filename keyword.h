//
// Created by ensar on 5/19/2021.
//
#include <stdarg.h>
#ifndef LEXICAL_WIN_KEYWORD_H
#define LEXICAL_WIN_KEYWORD_H
#define STRING_CONST 1
#define INT_CONST 2
#define VARIABLE 4



typedef struct wordKeyStruct {
    char *keyWord;
    struct wordKeyStruct *next;
    struct wordKeyStruct *afterPossibleKeyWords;
    unsigned char followUp;
} KeyWord;

KeyWord* getKeyWord(char *keyWord, KeyWord *keyWordRoot);

unsigned char setFollowUps(char string_const, char int_const, char variable){
    return (string_const * STRING_CONST) | (int_const * INT_CONST) | (variable * VARIABLE);
}

KeyWord* setAfterPossibleKeywords(KeyWord* head, int n_args, ...){
    KeyWord* retVal = malloc(sizeof(KeyWord*) * n_args);
    va_list list;
    va_start(list, n_args);
    for (int i = 0; i < n_args; ++i) {
        set->afterPossibleKeyWords[i] = *getKeyWord(va_arg(list, char*), head);
    }
    va_end(list);
    return retVal;
}

KeyWord *createKeyword(char *keyWord, KeyWord *prev) {
    KeyWord *nKeyWord;
    nKeyWord = (KeyWord *) malloc(sizeof(KeyWord));
    nKeyWord->keyWord = malloc(strlen(keyWord));
    strcpy(nKeyWord->keyWord, keyWord);
    prev->next = (KeyWord *) malloc(sizeof(KeyWord*));
    prev->next = nKeyWord;
    nKeyWord->next = NULL;
    return nKeyWord;
}

KeyWord *createKeyWordLinkedList() {
    KeyWord *head;
    KeyWord *curr;
    head = malloc(sizeof(KeyWord));
    head->keyWord = malloc(3);
    strcpy(head->keyWord, "int");
    // int 0
    curr = head;
    // move 1
    curr = createKeyword("move", curr);
    // add 2
    curr = createKeyword("add", curr);
    // sub 3
    curr = createKeyword("sub", curr);
    // out 4
    curr = createKeyword("out", curr);
    // loop 5
    curr = createKeyword("loop", curr);
    // [ 6
    curr = createKeyword("[", curr);
    // ] 7
    curr = createKeyword("]", curr);
    // times 8
    curr = createKeyword("times", curr);
    // newline 9
    curr = createKeyword("newline", curr);
    // to 10
    curr = createKeyword("to", curr);
    // . 11
    curr = createKeyword(".", curr);
    // , 12
    curr = createKeyword(",", curr);
    // from 13
    curr = createKeyword("from", curr);


    curr = head;
    // int
    curr->followUp = setFollowUps(0,0,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, ".");
    curr = curr->next;
    // move
    curr->followUp = setFollowUps(0,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "to");
    curr = curr->next;
    // add
    curr->followUp = setFollowUps(0,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "to");
    curr = curr->next;
    // sub
    curr->followUp = setFollowUps(0,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "from");
    curr = curr->next;
    // out
    curr->followUp = setFollowUps(1,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 2, ",", ".");
    curr = curr->next;
    // loop
    curr->followUp = setFollowUps(0,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "times");
    curr = curr->next;
    // [
    curr->followUp = 0;
    curr->afterPossibleKeyWords = NULL;
    curr = curr->next;
    // ]
    curr->followUp = 0;
    curr->afterPossibleKeyWords = NULL;
    curr = curr->next;
    // times
    curr->followUp = setFollowUps(0,0,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "[");
    curr = curr->next;

    curr->followUp = setFollowUps(0,1,1);
    curr->afterPossibleKeyWords = setAfterPossibleKeywords(head, 1, "times");
    curr = curr->next;
    return head;
}

KeyWord* getKeyWord(char *keyWord, KeyWord *keyWordRoot) {
    KeyWord *curr = keyWordRoot;
    char i = 0;
    while (curr != NULL) {
        if (strcmp(curr->keyWord, keyWord) == 0) return curr;
        curr = curr->next;
        i++;
    }
    return NULL;
}

void freeKeyWordLinkedList(KeyWord *head) {
    KeyWord *temp;
    while (head) {
        free(head->keyWord);
        if (head->next) {
            temp = head;
            head = head->next;
            free(temp);
        } else {
            free(head);
            break;
        }
    }
}

bool isIntConstant(char *str) {
    if (!(str[0] == '-' || (str[0] >= 48 && str[0] < 58))) return false;
    for (int i = 1; i < strlen(str); i++) if (!(str[i] >= 48 && str[i] < 58)) return false;
    return true;
}

bool isVariable(char *str) {
    if (!((str[0] >= 65 && str[0] < 91) || (str[0] >= 97 && str[0] < 123))) return false;
    for (int i = 0; i < strlen(str); i++)
        if (!((str[i] >= 65 && str[i] < 91) ||
              (str[i] >= 97 && str[i] < 123)))
            return false;
    return true;
}

bool isStringConstant(char *str, LineTracker *tracker) {
    if (str[0] == LEXEME_STRING) {
        if (str[strlen(str) - 1] == LEXEME_STRING) return true;
        fprintf(stderr, "String constant does not close at line: %d", getLine(tracker));
        exit(4);
    }
    return false;
}


#endif //LEXICAL_WIN_KEYWORD_H
