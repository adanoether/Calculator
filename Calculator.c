/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 05 - Calculatrice
 Fichier     : Calculator.c
 Auteur(s)   : Ohan Mélodie,
 Date        : 04.06.2020

 But         : Provides the declaration of functions needed for the
               calculator.

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include "Stack.h"
#include "ctype.h"  // bool
#include "Calculator.h"

#define UNARY_PLUS      '+'
#define UNARY_MINUS     '-'

//  Output
// --------------------------------------------------------------------------------

void displayMessage(Error msg){
  switch (msg) {
    case ERR_SYNTAX              : printf(EMSG_SYNTAX_ERROR "\n");    break;
    case ERR_DIVIDE_BY_ZERO      : printf(EMSG_DIVIDE_BY_ZERO "\n");  break;
    case ERR_OPERATORS           : printf(EMSG_OPERATOR "\n");        break;
    case ERR_UNKNOWN_CMD         : printf(EMSG_UNKNOWN_CMD "\n");     break;
    case ERR_NOT_END_CHAR        : printf(EMSG_NOT_END_CHAR "\n");    break;
    case ERR_OUT_OF_RANGE_ERROR  : printf(EMSG_OUT_OF_RANGE "\n");    break;
    default: break;
  }
}

// Operator's function
// --------------------------------------------------------------------------------

Operator getOperatorIndex(char c){
  switch (c) {
    case '+':  return PLUS;
    case '-':  return MINUS;
    case '*':  return MULTIPLICATION;
    case '/':  return DIVISION;
    case '=':  return EQUAL;
    default :  return NOT_SUPPORTED;
  }
}


Error polishNotationSolve(Stack* st,  const int op){

  Operator id = getOperatorIndex(op);

  if(id == NOT_SUPPORTED)
    return ERR_OPERATORS;

  if(id == EQUAL)
    return NONE;

  if(st->size <= 1)
    return ERR_SYNTAX;

  // extracts lhs if rhs does not end with 0 and there is no division
  int* rhs = top(st);
  if(*rhs == 0 && id == DIVISION){
    return ERR_DIVIDE_BY_ZERO;
  }

  int* lhs = pop(st);
  pop(st);

  // push in this stack result of operation depending of the input operator
  switch (id) {
    case PLUS:           push(st, *lhs + *rhs);  break;
    case MINUS:          push(st, *lhs - *rhs);  break;
    case MULTIPLICATION: push(st, *lhs * *rhs);  break;
    case DIVISION:       push(st, *lhs / *rhs);  break;
  }

  return NONE;
}



//  Input's function
// --------------------------------------------------------------------------------

int fpeek(FILE *stream){
    int c;
    c = fgetc(stream);
    ungetc(c, stream);
    return c;
}

bool isUnary(char input, char nextInput) {
  return ((input == UNARY_PLUS || input == UNARY_MINUS) && isdigit(nextInput));
}

bool isQuitCmd(char input){
    return toupper((int)input) == toupper((int)QUIT_CMD);
}

Command getCommand(){
    int input = fpeek(stdin);
    while (getchar() != '\n');
    fflush(stdin);
    if (toupper(input) == QUIT_CMD)
        return CMD_QUIT;
    else if(toupper(input) == RESTART_CMD)
        return CMD_RESTART;
    return CMD_UNKNOWN;
}

bool isInputCmd(){
    int input;
    do{
        input = fpeek(stdin);
        if(isalpha(input)){
            return true;
        }else{
            return false;
        }
    }while (getchar() != WS_CHAR);
}

Error solve(int* result){
  char  alphaInput;       // will contain current alphanum
  int   digitInput,       // will contain current digit
  next;                   // next "char" in the input sequence
  int sign = 1;           // to manage unary minus sign case

  Error error = NONE;     // result of input

  Stack st;               // will contain the operands
  initialize(&st);
  bool isNegative = false;

  do{ // loop until getchar() != '\n'

    next = fpeek(stdin);

    // digit processing
    // push digit in the stack if next input is not an '\n'
    //________________________________________________________
    if(isdigit(next)){

      scanf("%d", &digitInput);

      if((char)fpeek(stdin) != '\n'){
        push(&st, digitInput);
      }else {
        printf("ICI");
        error = ERR_SYNTAX;
      }

      // alphanum processing
      // 3 cases: syntax error, unary operator and solve
      //________________________________________________________
    }else{
      // extract current et next input
      scanf("%c", &alphaInput);
      next = fpeek(stdin);

      Operator  op = getOperatorIndex(alphaInput);

      // To protect against wrong format
      if((st.size <= 0 && op == EQUAL)       ||   // if the user only types =
         (op != EQUAL && (char)next == '\n') ||   // If the sign = is forgotten
          (op == EQUAL && st.size >= 2))          // if an operator has been forgotten
        error = ERR_SYNTAX;

      // operator and unary processing
      //__________________________
      if(op != NOT_SUPPORTED && error == NONE){

        // if it's an unary operator case, we push it in the stack
        if(isUnary(alphaInput,next)){

          if(op == MINUS){
            scanf("%d",&digitInput);
            digitInput*=-1;
            push(&st,digitInput);
          }

          // if it's not an unary operator, solve current op.
        } else{
          error = polishNotationSolve(&st, alphaInput);
        }
      }
    } // else is digit

    if(error != NONE)
      break;

  }while (getchar() != '\n');
  fflush(stdin);
  // affect result if there is no error
  if(error == NONE)
    *result = *top(&st);
  if(st.size != 0)
    empty(&st);

  return error;
}
