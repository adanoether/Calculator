/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 05 - Calculatrice
 Fichier     : Stack.c
 Auteur(s)   : Ohan Mélodie
 Date        : 12.06.2020

 But         : Here you will find all the functions related to the battery.

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include "Stack.h"

void initialize(Stack* s){
    s->size      = 0;
    s->capacity  = 0;
    s->container = NULL;
}

Stack_type* top(const Stack* s){
    if(s->size!=0){
        return &(s->container[s->size-1]);
    }
    return NULL;
}

void empty(Stack* s){
    assert(s->size != 0);
    free((void*)s->container);
}

void push(Stack* s, Stack_type value){

    if (s->capacity == 0){
        s->capacity = 1;
        s->container  =  (Stack_type*)calloc(s->capacity, sizeof(Stack_type));
    } else if(s->size + 1 >= s->capacity){
        s->capacity *= 2;
        s->container = (Stack_type*)realloc(s->container, (s->capacity) * sizeof(Stack_type));
    }
    ++s->size;
    s->container[s->size-1] = value;
}


Stack_type* pop(Stack* s){
    assert(s->size != 0);
    free((void*)s->container[s->size-1]);
    --s->size;
    return (Stack_type*)&(s->container[s->size-1]);
}

#if DEBUG_MODE

void display(const Stack* s){
    printf("Stack size   : %d\n", s->size);
    printf("Stack content: ");
    printf("\n[");
    for(size_t i = s->size; i>0; --i) {
        if (i != s->size)
            printf(", ");
        printf("%"STACK_PRINT, s->container[i-1]);
    }
    printf("]\n");
}
#endif
