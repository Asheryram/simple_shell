#include "shell.h"

/**
 * expand_alias - expand the alias found in the command strings
 *
 * @arginv: args inventory
 * Return: int
 */
int expand_alias(arg_in_ven_tory_t *arginv)
{
	alias_t *node;
	tokens_t cmd_tokens;
	unsigned int i;
	char **commands;
	unsigned int count = 0;

	node = fetch_node_alias(arginv->alias, (char *)arginv->commands[0]);

	if (node != NULL)
	{
		gen_token(&cmd_tokens, node->command);
		count = 0;
		while (arginv->commands[count] != NULL)
		{
			count++;
		}
		commands = safe_malloc((count + cmd_tokens.tokensN) * sizeof(char *));
		for (i = count - 1; i >= 1; i--)
		{
			commands[i + cmd_tokens.tokensN - 1] =
				(char *)arginv->commands[i];
		}

		for (i = 0; i < cmd_tokens.tokensN; i++)
			commands[i] = _str_dupp((char *)cmd_tokens.tokens[i].str);
		free(arginv->commands[0]);
		free(arginv->commands);
		commands[count + cmd_tokens.tokensN - 1] = NULL;
		count = cmd_tokens.tokensN;
		arginv->commands = commands;
		del_tokens(&cmd_tokens);
		return (count - 1);
	}
	return (0);
}


/**
 * _getpid - gets the pid and starts a new child precess
 *
 * Return: returns the pid of new child process
 */
int _getpid(void)
{
	int pid;

	pid = fork();

	return (pid);
}

/**
 * bash_replace - replaces env vars
 * @arginv: arg inventory
 * @index: index of token_t struct array
 */
void bash_replace(arg_in_ven_tory_t *arginv, int index)
{
	unsigned int j;
	env_ment *node;
	tokens_t t = arginv->tokens;

	for (j = 0; j < _str_length(t.tokens[index].str); j++)
		if (t.tokens[index].str[j] == '$' && t.tokens[index].str[j + 1] != '\0')
			switch (t.tokens[index].str[j + 1])
			{
				case '$':
					repl_str_all((char **)&t.tokens[index].str,
						int_t_to_str_t(_getpid()), j, j + 1, 1);
					break;
				case '?':
					repl_str_all((char **)&t.tokens[index].str,
						int_t_to_str_t(arginv->exit_status), j,
						j + 1, 1);
					break;
				case '!':
						repl_str_all((char **)&t.tokens[index].str,
						(arginv->last_bg_pid == -1) ? "" :
						int_t_to_str_t(arginv->last_bg_pid), j,
						j + 1, 1);
					break;
				case '0':
					repl_str_all((char **)&t.tokens[index].str, "hsh", j,
						j + 1, 0);
						break;
				default:
					node = fetch_node(arginv->env_list,
							(char *)&t.tokens[index].str[j + 1]);
					repl_str_all((char **)&t.tokens[index].str,
							(node == NULL) ? "" : node->val, j,
							_str_length(t.tokens[index].str) - 1, 0);
					}
				else if (t.tokens[index].str[j] == '~' && j == 0)
				{
					node = fetch_node(arginv->env_list, "HOME");
					repl_str_all((char **)&t.tokens[index].str, node->val, j, j, 0);
				}
}

/**
 * expand_bash_vars - expand all variables found in the arginv strings
 *
 * @arginv: args inventory
 *
 */
void expand_bash_vars(arg_in_ven_tory_t *arginv)
{
	unsigned int i;
	tokens_t t = arginv->tokens;

	for (i = 0; i < t.tokensN; i++)
		if (t.tokens[i].id == TO_KEN_STRING)
			bash_replace(arginv, i);
}

