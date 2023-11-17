#include "clyrshell.h"

/**
* This is the main entery point
*/
int main(void)
{
    char cmmd[1024];

    while (1)
    {
		prompt_dollar_display();
        read_cmmd (cmmd,sizeof(cmmd) );

        char *command = strdup(cmmd);
        if (command == NULL) {
            write_str("Memory allocation error\n");
            _exit(EXIT_FAILURE);
        }

        cmmd_execution(cmmd);
        free(command);
    }

    return 0; 
}