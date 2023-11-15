#include "shell.h"

/**
 * _al_ias - builtin func to set alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _al_ias(arg_in_ven_tory_t *arginv)
{
	char *input, **combo, **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		write_alias(arginv->alias);
		return (EX_IT_SUC_CESS);
	}
	else if (commands[2] != NULL)
	{
		_process_err("alias: too many arguments.\n");
		return (-1);
	}

	input = commands[1];

	combo = se_pa_rate_string(input);

	if (modify_node_alias(&arginv->alias, combo[0], combo[1]) == EX_IT_FAI_LURE)
		add_node_alias(&arginv->alias, combo[0], combo[1]);

	free(combo[0]);
	free(combo[1]);
	free(combo);
	return (EX_IT_SUC_CESS);
}

/**
 * _un_al_ias - builtin func to unset alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _un_al_ias(arg_in_ven_tory_t *arginv)
{
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		_process_err("unalias: missing arguments.\n");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		_process_err("unalias: too many arguments.\n");
		return (-1);
	}

	if (remove_node_alias(&arginv->alias, commands[1]) == EX_IT_SUC_CESS)
		return (EX_IT_SUC_CESS);

	return (EX_IT_FAI_LURE);
}

/**
 * she_ll_helper - prints help commands info based on the other input argument
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int she_ll_helper(arg_in_ven_tory_t *arginv)
{
	char **commands;
	int i = 0, retval = 127;
	bins_t bins[] = {
		{"exit", help_exit}, {"env", help_env_ment},
		{"setenv", help_set_env_ment}, {"unsetenv", help_unsetenv},
		{"history", help_history}, {"cd", help_cd}, {"alias", help_alias},
		{"help", help_help},
		{NULL, NULL}
	};


	commands = (char **)arginv->commands;
	if (commands[2] != NULL)
	{
		_process_err("help: too many input commands.\n");
		return (retval);
	}

	while (bins[i].function != NULL)
	{
		if (_strg_com_pare(bins[i].function, commands[1]) == 0)
		{
			bins[i].help();
			retval = EX_IT_SUC_CESS;
			break;
		}
		i++;
	}

	return (retval);
}

/**
 * she_ll_close - exit status to exit
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int she_ll_close(arg_in_ven_tory_t *arginv)
{
	char **commands;
	int es;

	commands = (char **)arginv->commands;
	if (commands[1] == NULL)
		arginv->exit = 1;
	else if (is_unsgn_int(commands[1]))
	{
		es = _a_to_oi(commands[1]);
		arginv->exit = 1;
		arginv->exit_status = es;
	}
	else
		_process_err("exit: Illegal number\n");

	return (EX_IT_SUC_CESS);
}
