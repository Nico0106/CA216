 /*
utility.c
Author: Nicolas Oyeleye
*/

// includes
#include <stdio.h>
#include "myshell.h"

/*
Function: firstPrompt
@params: void
returns: void
Description: "$" is printed when the shell is waiting for the user to enter a command
*/
void firstPrompt(void){
    fprintf(stderr, "$ ");
}

/*
Function: secondPrompt
@params: void
returns: void
Description: ">>>" is printed by the shell when user enters a mutlti-line command
*/
void secondPrompt(void){

    fprintf(stderr, ">>> ");
}
