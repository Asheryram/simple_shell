#ifndef CLYRSHELL_H
#define CLYRSHELL_H

/*
* This is the standard libraries
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


 /**
  * This is the custom macros
  * 
  */
#define EXIT_FAILURE 1



/**
 * This is the custom funtions
 * 
 */
void prompt_dollar_display(void);
void  read_cmmd (char *cmmd,size_t s );
void cmmd_execution(char *cmmd);
void clyr_print(const char *m);



#endif 