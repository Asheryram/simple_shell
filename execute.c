#include "shell.h"

/**
 * is_path - checks if input command is part of directory PATH
 * @command: a command
 *
 * Return: 1 if path, 0 if no path
 */
int is_path(char *command)
{
	int i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (1);
		i++;
	}

		return (0);
}

/**
 * exec_builtins - custom function to exe_cute builtin commands
 * @arginv: arguments inventory
 *
 * Return: 1 on success, 0 on failure
 */
int exec_builtins(arg_in_ven_tory_t *arginv)
{
	int i, retval;
	/* old_stdout */
	char *str, **commands;
	builtins_t builtins_list[] = {

		{"env", _env_ment}, {"setenv", _set_env_ment},
		{"unsetenv", _un_set_env}, {"history", _past_time}, {"cd", _cee_dee},
		{"alias", _al_ias}, {"unalias", _un_al_ias}, {"help", she_ll_helper},
		{"exit", she_ll_close},
		{NULL, NULL}
	};

	retval = EX_IT_FAI_LURE;
	commands = (char **)arginv->commands;

	/* old_stdout = redirect_output(arginv, 0); */

	for (i = 0; ((str = builtins_list[i].command) != NULL); i++)
	{
		if (_strg_com_pare(str, commands[0]) == 0)
		{
			retval = builtins_list[i].builtin_func(arginv);
			break;
		}
	}

	arginv->exit_status = retval;
	return (retval);
}

/**
 * exec_error_exit - frees all and exits if exec error
 * @msg: message to display
 * @command: command to free
 * @_env_mentiron: env double pointer to free
 * @arginv: arg inventory to free
 */
void exec_error_exit(char *msg, char *command, char **_env_mentiron,
		arg_in_ven_tory_t *arginv)
{
	delete_pipeline(&arginv->pipeline);
	delete_parser(&arginv->parser);
	del_tokens(&arginv->tokens);
	free(command);
	free_paths(_env_mentiron);
	freeall(arginv);
	_process_err(msg);
	exit(1);
}

/**
 * exec_path - custom function to exe_cute from PATH
 * @command: command to exe_cute
 * @arginv: arg inventory
 *
 * Return: pid of parent
 */
pid_t exec_path(char *command, arg_in_ven_tory_t *arginv)
{
	pid_t pid;
	char **_env_mentiron;

	pid = fork();
	if (pid < 0)
	{
		_process_err("Critical error: unable to fork()!\n");
		exit(1);
	}

	if (pid == 0)
	{
		_env_mentiron = link_to_poin_ter(arginv->env_list);

		if (execve(command, (char **)arginv->commands, _env_mentiron) < 0)
			exec_error_exit("No Command\n", command, _env_mentiron, arginv);
	}
	free(command);
	return (pid);
}

/**
 * exe_cute - completes execution of input commands
 * @arginv: arguments inventory
 *
 * Return: void
 */
pid_t exe_cute(arg_in_ven_tory_t *arginv)
{
	env_ment *env_list;
	char **commands;
	char *path, *command;
	char **paths;

	env_list = arginv->env_list;

	commands = (char **)arginv->commands;

	command = safe_malloc(sizeof(char) * BU_FFER_SIZE);
	command = _str_co_py(command, *commands);

	if (exec_builtins(arginv) == EXT_FAILURE)
	{
		if (is_path(command))
		{
			return (exec_path(command, arginv));
		}
		else
		{
			path = safe_malloc(sizeof(char) * BU_FFER_SIZE);
			locate_path(path, env_list);
			paths = gen_token_path(path);
			cat_path(paths, command);
			free_paths(paths);
			free(path);
			return (exec_path(command, arginv));
		}
	}
	free(command);
	return (-1);
}
