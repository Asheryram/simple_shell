#include "shell.h"


/**
 * sig_handler - handles user input of ^C with the following
 * @sig: integer value of signal to change, will be SIGINT = ^C
 *
 * Return: void
 */
void sig_handler(int sig)
{
	(void) sig;
	_puts("");
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - custom shell
 * Return: 0
 */
int main(void)
{
	arg_in_ven_tory_t *arginv;
	int exit_status;

	arginv = build_arg_inv();
	signal(SIGINT, sig_handler);
	while (!arginv->exit)
	{
		if (arginv->st_mode)
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		if (!_get_line(&arginv->input_commands, &arginv->buflimit))
			break;
		add_node_history(&arginv->history, arginv->input_commands);

		gen_token(&arginv->tokens, arginv->input_commands);

		if (arginv->tokens.tokensN > 0)
		{
			expand_bash_vars(arginv);

			if (parse(&arginv->parser, &arginv->tokens))
			{
				delete_parser(&arginv->parser);
				del_tokens(&arginv->tokens);
				continue;
			}

			process_exe_cute(arginv);
			delete_parser(&arginv->parser);
		}

		mem_reset(arginv->input_commands, BU_FFER_SIZE);

		del_tokens(&arginv->tokens);
	}
	exit_status = freeall(arginv);

	return (exit_status);
}
