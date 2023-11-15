#include "shell.h"

/**
 * file_path - assembles path to cd into
 * @commands: array of pointer pointg to commands
 * @env_list: head of env linked list
 *
 * Return: full filepath
 */
char *file_path(char **commands, env_ment *env_list)
{
	env_ment *fetched_home, *fetched_old;
	int hyphen;
	char *path;

	path = safe_malloc(1024);

	fetched_home = fetch_node(env_list, "HOME");
	fetched_old = fetch_node(env_list, "OLDPWD");

	if (commands[1] != NULL)
		hyphen = _strng_com_pare(commands[1], "-", 1);

	if (commands[1] == NULL)
		path = _str_co_py(path, fetched_home->val);
	else if (hyphen == 0)
		path = _str_co_py(path, fetched_old->val);
	else if (commands[1][0] == '/')
		path = _str_co_py(path, commands[1]);
	else
	{
		getcwd(path, 1024);
		_strn_cat(path, "/", 1);
		_strn_cat(path, commands[1], _str_length(commands[1]));
	}

	return (path);
}


/**
 * _cee_dee - builtin cd function
 * @arginv: arg inventory
 *
 * Return: 0 if good, -1 if bad
 */
int _cee_dee(arg_in_ven_tory_t *arginv)
{
	char *path, *oldpwd, *pwd, **commands;
	int check;

	oldpwd = safe_malloc(1024);
	pwd = safe_malloc(1024);

	getcwd(oldpwd, 1024);

	commands = (char **)arginv->commands;

	path = file_path(commands, arginv->env_list);

	check = chdir(path);

	if (check == -1)
	{
		free(oldpwd);
		free(pwd);
		free(path);
		return (2);
	}
	else
	{
		getcwd(pwd, 1024);
		put_node_env_ment_ment(&arginv->env_list, "PWD", pwd);
		put_node_env_ment_ment(&arginv->env_list, "OLDPWD", oldpwd);
	}
	free(oldpwd);
	free(pwd);
	free(path);

	return (0);
}
