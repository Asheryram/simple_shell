#include "shell.h"

/**
 * freeall - function to free all allocated memory
 * @arginv: args inventory
 *
 * Return: 0 on success, 1 on failure
 */
int freeall(arg_in_ven_tory_t *arginv)
{
	int exit_status;

	if (arginv)
	{
		perm_ali_as(arginv);
		file_history(arginv);
		free_history(arginv->history);
		free(arginv->history_file);
		free_env_mentiron(arginv->env_list);
		free_alias(arginv->alias);
		free(arginv->alias_file);
		if (arginv->input_commands)
			free(arginv->input_commands);
		exit_status = arginv->exit_status;
		free(arginv);
	}
	return (exit_status);
}

/**
 * free_alias - function to free all allocated memory
 * @head: head of alias
 *
 * Return: 0 on success, 1 on failure
 */
int free_alias(alias_t *head)
{
	alias_t *temp = head;

	while (head)
	{
		temp = temp->next;
		free(head->alias);
		free(head->command);
		free(head);
		head = temp;
	}

	return (EX_IT_SUC_CESS);
}

/**
 * free_env_mentiron - function to free all allocated memory
 * @head: head of custom _env_mentiron
 *
 * Return: 0 on success, 1 on failure
 */
int free_env_mentiron(env_ment *head)
{
	env_ment *temp = head;

	while (head)
	{
		temp = temp->next;
		free(head->var);
		free(head->val);
		free(head);
		head = temp;
	}

	return (EX_IT_SUC_CESS);
}

/**
 * free_history - function to free all allocated memory
 * @head: history linked list
 *
 * Return: 0 on success, 1 on failure
 */
int free_history(history_t *head)
{
	history_t *temp = head;

	while (head)
	{
		temp = temp->next;
		free(head->command);
		free(head);
		head = temp;
	}

	return (EX_IT_SUC_CESS);
}
