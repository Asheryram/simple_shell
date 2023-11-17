#include "clyrshell.h"
/*
* This is a custom print function
*/
void clyr_print(const char *m)
{
    write(STDOUT_FILENO , m ,strlen(m));
}