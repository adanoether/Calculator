/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 05 - Calculatrice
 Fichier     : Stack.h
 Auteur(s)   : Mélodie Uhan,Kevin Farine
 Date        : 04.06.2020

 But         : Provides all the structures and prototpyes required for a stack.

 Remarque(s) : in the case of a battery, the capacity is doubled if a push has to
               be made.
               Only the empty function properly destroys the battery.

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define Stack_type int     // all values will have this type

#define DEBUG_MODE   1     // Provides display function
#define STACK_PRINT "d"    // use to printf STACK Types values

// capacity
typedef struct {
  Stack_type*   container;
  size_t        size;
  size_t        capacity;
} Stack;

/**
 * @brief   Initialize stack size to 0 and his container to null pointer
 * @param   Stack s
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
void initialize(Stack* s);

/**
 * @brief   Return current top stack value address
 * @param   Stack s
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
Stack_type* top(const Stack* s);

/**
 * @brief   Empty the stack. If the stack was already empty,
 *          this function abort the program.
 * @param   Stack s
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
void empty(Stack* s);

/**
 * @brief   Push an element at the top of the stack.
 * @details It reallocates memory if stack's containers is empty or
 *          reserve 1 spot  in memory if it's needed.
 * @param   Stack s
 * @return  false if an error has occurred
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
void push(Stack* s, Stack_type value);

/**
 * @brief   Remove the top element of the stack and return the new top adress
 *          If the stack is empty, this function abort the program.
 * @param   Stack s
 * @return  STACK_T pointer value of the top
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
Stack_type* pop(Stack* s);

#if DEBUG_MODE
/**
 * @brief   Display all information about the stack (size and content).
 * @param   Stack s
 * @date    06/06/2020
 * @authors Ohan Mélodie
 */
void display(const Stack* s);

#endif
#endif //STACK_H
