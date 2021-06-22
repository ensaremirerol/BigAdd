//
// Created by ensar on 6/12/2021.
//

#include "bigint.h"

BigInt *strtobigInt(char* str){
    BigInt *result = malloc(sizeof (BigInt));
    BigIntNode *currNode = malloc(sizeof (BigIntNode));
    result->root = currNode;
    currNode->prev = NULL;
    result->size = 0;
    char* currStr = calloc(sizeof (char), DECIMAL_SEP + 1);
    char* str2long = currStr;
    if(str[0] == '-'){
        result->isNegative = true;
        str += 1;
    } else result->isNegative = false;
    while (str[0] == '0' && strlen(str) > 1) str += 1;
    long long i = strlen(str) - 1;
    while (i >= 0) {
        result->size += 1;
        i -= DECIMAL_SEP;
        if(i < 0){
            strncpy(currStr, str, i + DECIMAL_SEP + 1);
        }
        else{
            strncpy(currStr, (str + i + 1), DECIMAL_SEP);
        }
        while (str2long[0] == '0') str2long += 1;
        currNode->number = strtoll(str2long, NULL, 0);
        if(i >= 0){
            currNode->next = malloc(sizeof (BigIntNode));
            currNode->next->prev = currNode;
        }
        else currNode->next = NULL;
        currNode = currNode->next;
        for (int j = 0; j < DECIMAL_SEP; ++j) {
            currStr[j] = 0;
        }
        str2long = currStr;
    }
    free(currStr);
    return result;
}

void addBigInt(BigInt* dest, BigInt* number){
    BigInt *tdest, *tnumber;
    bool swap;
    if(dest->isNegative && !number->isNegative){
        switch (compareAbsVal(dest, number)) {
            case 0:
            case 1:{
                tdest = dest;
                tnumber = number;
                swap = false;
                break;
            }
            case -1:{
                tdest = copyBigInt(number);
                tdest->isNegative = false;
                tnumber = dest;
                swap = true;
            }
        }
        subbi_internal(tdest, tnumber);
    }
    else if (!dest->isNegative && number->isNegative){
        switch (compareAbsVal(dest, number)) {
            case 0:
            case 1:{
                tdest = dest;
                tnumber = number;
                swap = false;
                break;
            }
            case -1:{
                tdest = copyBigInt(number);
                tdest->isNegative = true;
                tnumber = dest;
                swap = true;
            }
        }
        subbi_internal(tdest, tnumber);
    }
    else{
        addbi_internal(dest, number);
        swap = false;
    }
    if(swap){
        freeBigIntNode(dest->root);
        dest->size = tdest->size;
        dest->root = tdest->root;
        dest->isNegative = tdest->isNegative;
        free(tdest);
    }

}
void addbi_internal(BigInt* dest, BigInt* number){
    int carry = 0;
    BigIntNode *destNode = dest->root, *otherNode = number->root;
    while (otherNode){
        destNode->number += otherNode->number + carry;
        carry = 0;
        if(destNode->number >= NODE_MAX_VAL){
            destNode->number -= NODE_MAX_VAL;
            carry = 1;
        }
        if(destNode->next == NULL && otherNode->next){
            destNode->next = calloc(sizeof (BigIntNode), 1);
            destNode->next->prev = destNode;
            dest->size += 1;
        }
        if(otherNode->next)destNode = destNode->next;
        otherNode = otherNode->next;
    }
    if(carry == 1){
        if(destNode->next == NULL){
            destNode->next = calloc(sizeof (BigIntNode), 1);
            destNode->next->prev = destNode;
        }
        destNode = destNode->next;
        dest->size += 1;
        destNode->number = carry;
    }
    tidyBigInt(dest);
}

// TODO: Rewrite
void subBigInt(BigInt* dest, BigInt* number){
    BigInt *tdest, *tnumber;
    bool swap;
    if(dest->isNegative && number->isNegative){
        switch (compareAbsVal(dest, number)) {
            case 0:
            case 1:{
                tdest = dest;
                tnumber = number;
                swap = false;
                break;
            }
            case -1:{
                tdest = copyBigInt(number);
                tdest->isNegative = false;
                tnumber = dest;
                swap = true;
            }
        }
        subbi_internal(tdest, tnumber);
    }
    else if (!dest->isNegative && !number->isNegative){
        switch (compareAbsVal(dest, number)) {
            case 0:
            case 1:{
                tdest = dest;
                tnumber = number;
                swap = false;
                break;
            }
            case -1:{
                tdest = copyBigInt(number);
                tdest->isNegative = true;
                tnumber = dest;
                swap = true;
            }
        }
        subbi_internal(tdest, tnumber);
    }
    else{
        addbi_internal(dest, number);
        swap = false;
    }
    if(swap){
        freeBigIntNode(dest->root);
        dest->size = tdest->size;
        dest->root = tdest->root;
        dest->isNegative = tdest->isNegative;
        free(tdest);
    }
}

void subbi_internal(BigInt* dest, BigInt* number){
    BigIntNode *destNode = dest->root, *otherNode = number->root;
    while (otherNode){
        destNode->number -= otherNode->number;
        if(destNode->number < 0){
            destNode->number += NODE_MAX_VAL;
            destNode->next->number -= 1;
        }
        if(otherNode->next) destNode = destNode->next;
        otherNode = otherNode->next;
    }
    tidyBigInt(dest);
}

void printBigInt(BigInt* number){
    if(number->isNegative) printf("-");
    printbigIntNode(number->root);
}

void printbigIntNode(BigIntNode* node){
    if(node->next){
        printbigIntNode(node->next);
        for (char i = digitCount(node->number); i < DECIMAL_SEP; ++i) printf("0");
    }
    printf("%lld", node->number);
}

char digitCount(long long num){
    if (num == 0) return 1;
    char result = 0;
    while (num != 0){
        num /= 10;
        result++;
    }
    return result;
}

void tidyBigInt(BigInt* number){
    BigIntNode *currNode = number->root;
    BigIntNode *temp = NULL;
    bool clean = false;
    while (currNode){
        if(currNode->number == 0){
            if(temp==NULL) temp = currNode;
            clean = true;
        } else{
            temp = NULL;
            clean = false;
        }
        currNode = currNode->next;
    }
    if(clean && temp && number->size > 1){
        currNode = temp;
        if(currNode == number->root)
            currNode = currNode->next;
        currNode->prev->next = NULL;
        freeBigIntNode(currNode);
    }
    currNode = number->root;
    int newSize = 0;
    for (newSize; currNode; ++newSize) currNode = currNode->next;
    number->size = newSize;
}

BigInt *copyBigInt(BigInt *number){
    BigInt *result = malloc(sizeof (BigInt));
    result->isNegative = number->isNegative;
    result->size = 0;
    result->root = malloc(sizeof (BigIntNode));
    BigIntNode *numCurr = number->root;
    BigIntNode *copyCurr = result->root;
    copyCurr->prev == NULL;
    while (numCurr){
        copyCurr->number = numCurr->number;
        if(numCurr->next){
            copyCurr->next = malloc(sizeof (BigIntNode));
            copyCurr->next->prev = copyCurr;
            result->size += 1;
        }
        else copyCurr->next = NULL;
        numCurr = numCurr->next;
        copyCurr = copyCurr->next;
    }
    return result;
}

int compare(BigInt* num1, BigInt* num2){
    if(!num1->isNegative && num2->isNegative) return 1;
    if(num1->isNegative && !num2->isNegative) return -1;
    if(num1->isNegative){
        if(num1->size > num2->size) return -1;
        else if(num1->size < num2->size) return 1;
        else return compareNode(num1->root, num2->root) * -1;

    }
    else{
        if(num1->size > num2->size) return 1;
        else if(num1->size < num2->size) return -1;
        else return compareNode(num1->root, num2->root);
    }
}

int compareAbsVal(BigInt* num1, BigInt* num2){
    if(num1->size > num2->size) return 1;
    else if(num1->size < num2->size) return -1;
    else return compareNode(num1->root, num2->root);
}

int compareNode(BigIntNode *node1, BigIntNode *node2){
    int result;
    if(node1->next && node2->next){
        result = compareNode(node1->next, node2->next);
    }
    else{
        if(node1->number == node2->number) result = 0;
        else result = node1->number > node2->number?1:-1;
    }
    if(result != 0) return result;
    else{
        if(node1->number == node2->number) result = 0;
        else result = node1->number > node2->number?1:-1;
        return result;
    }
}

void freeBigIntNode(BigIntNode* node){
    BigIntNode *temp;
    while (node){
        temp = node;
        node = node->next;
        free(temp);
    }
}

void freeBigInt(BigInt* number){
    BigIntNode *curr, *temp;
    curr = number->root;
    while (curr){
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(number);
}
