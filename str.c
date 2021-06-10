//
// Created by ensar on 6/9/2021.
//

#include "str.h"

// Clears given char array
void strclr(char* str, unsigned int size) {
    for (int i = 0; i < size; i++) str[i] = 0;
}