#include "clyrshell.h"
/**
 * 
 *This file is for execution 
 *
 */
void cmmd_execution(char *cmmd)
{
    pid_t p_pid = fork();

    switch (p_pid)
    {
    case -1:
        perror("fork");
        _exit(EXIT_FAILURE);
        break;
    case 0:
    {

        char *args[] = {cmmd, NULL};
        if (execve(command, args, NULL) == -1)
        {
            perror("execve");
            _exit(EXIT_FAILURE);
        }
        break;
    }
    default:
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            _exit(EXIT_FAILURE);
        }
        break;
    }
}