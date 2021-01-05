/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 05 - Calculatrice
 Fichier     : Calculator.h
 Auteur(s)   : Mélodie Uhan,
 Date        : 04.06.2020

 But         : Provides the prototype, const and structure needed for the
               calculator.

 Remarque(s) :

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Stack.h"
#include "ctype.h"  // bool

// --------------------------------------------------------------------------------
//                              TEXT MESSAGES
// --------------------------------------------------------------------------------

// Input message
#define MSG_INPUT             "Calcul: "

// Errors messages
#define EMSG_LABEL            "Erreur: "
#define EMSG_SYNTAX_ERROR     EMSG_LABEL "Syntaxe incorrecte."
#define EMSG_DIVIDE_BY_ZERO   EMSG_LABEL "Division par zero, calcul abandonnee."
#define EMSG_OPERATOR         EMSG_LABEL "Absence d'operateurs ou operateur inconnu."
#define EMSG_UNKNOWN_CMD      EMSG_LABEL "Commande inconnue."
#define EMSG_OUT_OF_RANGE     EMSG_LABEL "Vous avez depasse le nbre de car autorises."
#define EMSG_NOT_END_CHAR     EMSG_LABEL "Doit terminer par un '=' ."

// --------------------------------------------------------------------------------
//                                SETTINGS
// --------------------------------------------------------------------------------

#define STR_LEN_MAX     80
#define END_CHAR        '='
#define WS_CHAR         ' '
#define QUIT_CMD        'Q'
#define RESTART_CMD     'R'


//Type of error
typedef  enum{
  NONE,
  ERR_SYNTAX,
  ERR_DIVIDE_BY_ZERO,
  ERR_OPERATORS,
  ERR_UNKNOWN_CMD,
  ERR_OUT_OF_RANGE_ERROR,
  ERR_NOT_END_CHAR
} Error;

//Type of command
typedef enum{
  CMD_QUIT,
  CMD_RESTART,
  CMD_UNKNOWN
} Command;

//Type of operator
typedef enum{
  PLUS,
  MINUS,
  MULTIPLICATION,
  DIVISION,
  EQUAL,
  NOT_SUPPORTED
} Operator;


// --------------------------------------------------------------------------------
//                          CALCULATOR FUNCTIONS
// --------------------------------------------------------------------------------

//  Output
// --------------------------------------------------------------------------------

/**
 * @brief   Display message depending of error message code
 * @param   Error msg
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
void displayMessage(Error msg);

// Operator's function
// --------------------------------------------------------------------------------

/**
 * @brief   Get the index of operator
 * @param   c
 * @return  return the index of operator
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
Operator getOperatorIndex(char c);

/**
 * @brief   calculate the result while using value and operator from stack
 * @param   Stack st
 * @param   input
 * @return
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
Error polishNotationSolve(Stack* st,  const int op);


//  Input's function
// --------------------------------------------------------------------------------

/**
 * @brief   get the next character from buffer without erase it.
 * @param   stream
 * @return  return the value of the character
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
int fpeek(FILE *stream);

/**
 * @brief   check if current input is an unary operator
 * @param   input
 * @param   nextInput
 * @param   sign
 * @return  return the statement
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
bool isUnary(char input, char nextInput);

/**
 * @brief   Control if the Quit Command is called
 * @param   input
 * @return  return the statement
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
bool isQuitCmd(char input);

/**
 * @brief   check the command used
 * @param   input
 * @return  return the command used
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
Command getCommand();


/**
 * @brief   check if it's a right command
 * @return  return the statement
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
bool isInputCmd();

/**
 * @brief   Retrieves character by character the mathematical
 *          equation entered by the user. The expected format
 *          is reverse Polish notation.
 * @return  The error code if there is one or the NONE code
 *          if there is none.
 * @date    12/06/2020
 * @authors , Ohan Mélodie
 */
Error solve(int* result);


#endif // CALCULATOR_H
