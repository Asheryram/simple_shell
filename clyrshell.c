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
        cmmd_execution(cmmd);
    }

    return 0; 
}