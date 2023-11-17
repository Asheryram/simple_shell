#include "clyrshell.h"
/*
* This file is for execution 
*/
void cmmd_execution(const char *cmmd)
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
        const char *cmd_casted = cmmd;  
        char *args[] = { (char *)cmd_casted, NULL };
        char *envp[] = { NULL };
        execve(cmmd, args, envp);
        perror("execve");
        exit(EXIT_FAILURE);
        break;
    }
    default:
        wait(NULL);
        break;
    }
}