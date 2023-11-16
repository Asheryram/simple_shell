#ifndef CLYRSHELL_H
#define CLYRSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// #include <sys/wait.h>

#define EXIT_FAILURE 1


void prompt_dollar_display(void);
void  read_cmmd (char *cmmd,size_t s );
void cmmd_execution(const char *cmmd);
void clyr_print(const char *m);



#endif 