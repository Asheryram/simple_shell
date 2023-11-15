#include "shell.h"

/**
 * _env_ment - writes env to stdout
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _env_ment(arg_in_ven_tory_t *arginv)
{
	env_ment *env_list = arginv->env_list;
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] != NULL)
	{
		_process_err("env: No such file or directory\n");
		return (-1);
	}

	print_list(env_list);

	return (EX_IT_SUC_CESS);
}

/**
 * _past_time - writes history to stdout
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _past_time(arg_in_ven_tory_t *arginv)
{
	history_t *historylist = arginv->history;

	write_history(historylist);

	return (EX_IT_SUC_CESS);
}

/**
 * _set_env_ment - sets new environmental variable
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _set_env_ment(arg_in_ven_tory_t *arginv)
{
	char **commands, *new_var, *new_val;
	env_ment *env_list = arginv->env_list;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL || commands[2] == NULL)
	{
		_process_err("setenv: missing parameters.\n");
		return (-1);
	}

	if (commands[3] != NULL)
	{
		_process_err("setenv: missing value.\n");
		return (-1);
	}

	new_var = commands[1];
	new_val = commands[2];

	if (put_node_env_ment_ment(&env_list, new_var, new_val) == EXT_FAILURE)
	{
		add_node_env_ment_ment(&env_list, new_var, new_val);
	}

	return (EX_IT_SUC_CESS);
}

/**
 * _un_set_env - sets new environmental variable
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _un_set_env(arg_in_ven_tory_t *arginv)
{
	char **commands;
	env_ment *env_list = arginv->env_list;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		_process_err("unsetenv: missing parameters.\n");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		_process_err("unsetenv: too many input commands.\n");
		return (-1);
	}

	if (del_node_env_ment_ment(&env_list, commands[1]))
		return (EXT_FAILURE);

	return (EX_IT_SUC_CESS);
}
