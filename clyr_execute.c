#include "clyrshell.h"

void cmmd_execution(const char *cmmd){
    pid_t p_pid = fork();

    switch (p_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execlp(cmmd,cmmd,(char *)NULL);
        perror("exelp");
        exit(EXIT_FAILURE);
        break;
    default:
        wait(NULL);
        break;
    }
}