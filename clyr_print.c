#include "clyrshell.h"

void clyr_print(const char *m){
    write(STDOUT_FILENO , m ,strlen(m));
}