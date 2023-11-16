#include "clyrshell.h"

void  read_cmmd (char *cmmd,size_t s ){
    if (fgets(cmmd,s ,stdin) == NULL){
        if(feof(stdin)){
            clyr_print("\n");
            exit(EXIT_SUCCESS);
        } else {
            clyr_print("Error reading the given input");
            exit(EXIT_FAILURE);
        }
    }
    cmmd[strcspn(cmmd,"\n")] = '\0';
}