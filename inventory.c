#include "shell.h"

/**
 * build_arg_inv - function to build a struct of the arguments inventory
 * Return: pointer to arguments inventory struct
 */
arg_in_ven_tory_t *build_arg_inv(void)
{
	arg_in_ven_tory_t *arginv;

	arginv = safe_malloc(sizeof(arg_in_ven_tory_t));
	arginv->input_commands = safe_malloc(BU_FFER_SIZE * sizeof(char));
	arginv->env_list = env_list();
	arginv->buflimit = BU_FFER_SIZE;
	arginv->st_mode = _file_mode(STDIN_FILENO);
	arginv->last_bg_pid = -1;
	arginv->n_bg_jobs = 0;
	arginv->exit = 0;
	arginv->exit_status = 0;

	/* initialize history and history file */
	arginv->history_file = set_name(arginv->env_list, "/.simple_shell_history");
	arginv->history = history_list(arginv);

	/* initialize the aliases and alias file */
	arginv->alias_file = set_name(arginv->env_list, "/.simple_shell_alias");
	arginv->alias = alias_list();
	up_load_al_ias(arginv);

	return (arginv);
}

/**
 * set_name - appends home directory absolure path to filename
 * @env_list: the linked list to environ variables
 * @name: the name of the file to be written
 *
 * Return: char pointer to filename
 */
char *set_name(env_ment *env_list, char *name)
{
	char *file, *home;
	int lenhome, lenname;
	env_ment *home_node;

	home_node = fetch_node(env_list, "HOME");
	home = home_node->val;

	lenhome = _str_length(home);
	lenname = _str_length(name);

	file = safe_malloc(sizeof(char) * (lenhome + lenname + 1));
	file = _strn_cat(file, home, lenhome);
	file = _strn_cat(file, name, lenname);

	return (file);
}
