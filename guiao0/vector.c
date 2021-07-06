#include "vector.h"
#include <stdlib.h>
#include <stdio.h>


void fill(int* vector, int size, int value) {
    int i;
    for (i=0; i<size; i++) {
        vector[i] = value;
    }
}

int find(int* vector, int size, int value) {
    int i, r=-1;
    for (i=0; i<size; i++) {
        if (vector[i] == value) {
            r = i;
            break;
        } 
    }
    return r;
}