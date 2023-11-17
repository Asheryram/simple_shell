#include "clyrshell.h"

/**
* This is the main entery point
*/
int main(void)
{
    char cmmd[1024];
     char *command = strdup(cmmd);

    while (1)
    {
		prompt_dollar_display();
        read_cmmd (cmmd,sizeof(cmmd) );

       
        if (command == NULL) {
            clyr_print("Memory allocation error\n");
            _exit(EXIT_FAILURE);
        }

        cmmd_execution(cmmd);
        free(command);
    }

    return 0; 
}