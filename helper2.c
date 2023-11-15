#include "shell.h"

/**
 * help_history - help function to explain how the associated function works
 */
void help_history(void)
{
	_puts("\nUsage: $ history");
	_puts("Display the history list.");
}


/**
 * help_unsetenv - help function to explain how the associated function works
 */
void help_unsetenv(void)
{
	_puts("\nUsage: $ unsetenv [NAME]");
	_puts("\tUnsets a saved environmental variable");
}

/**
 * help_set_env_ment - help function to explain how the associated function works
 */
void help_set_env_ment(void)
{
	_puts("\nUsage: $ setenv [NAME] [VALUE]");
	_puts("\tSets a new environmental variable");
}