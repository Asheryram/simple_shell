#include "clyrshell.h"

int main(void){
    char cmmd[128];

    while (1){
        prompt_dollar_display();
        read_cmmd (cmmd,sizeof(cmmd) );
        cmmd_execution(cmmd);
    }

    return 0; 
}