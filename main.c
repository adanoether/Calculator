/*
 -----------------------------------------------------------------------------------
 Laboratoire : Labo 05 - Calculatrice
 Fichier     : main.c
 Auteur(s)   : Ohan Mélodie
 Date        : 04.06.2020

 But         : Main file for using the Reverse Polish Calculator.
 Remarque(s) : The purpose of this program is to make it possible to perform
               calculations according to reverse Polish notation.

                The two formats handled by the program are
                ° 1 2 + 4 * 3 + =
                ° 3 4 1 2 + * + =
                Both of them calculate this : ((1 + 2) * 4) + 3
                If a syntax error is detected, the user is notified.

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS

#include "Calculator.h"

#define MSG_PROGRAMME "Ce programme est une calculatrice base sur "\
                      "la notation polonaise inverse."



int main() {
  printf(MSG_PROGRAMME "\n\n");

  int res;
  Command c = CMD_RESTART;

  do{
      printf("Calcul : ");

      Error err = solve(&res);
      if (err == NONE){
          printf("Le resultat est : %d \n", res);
      }else{
          displayMessage(err);
      }

      do{
         printf("Voulez-vous recommencer ? (Q:quitter, R: recommencer) : \n");
         c = getCommand();
      }while (c == CMD_UNKNOWN);

  }while(c == CMD_RESTART);

  return EXIT_SUCCESS;
}
