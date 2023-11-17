#include "clyrshell.h"
/**
 * const char *cmmd
 * 
 *  This 
 */
* This file is for execution 

*/
void cmmd_execution()
{
    pid_t p_pid = fork();

    switch (p_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
    {
       
        char *argv[2];
        argv[0] ="/bin/sh";
        argv[1] = NULL;
        execve(argv[0], argv, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
        break;
    }
    default:
        wait(NULL);
        break;
    }
}