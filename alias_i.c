#include "shell.h"

/**
 * alias_list - builtin func to set alias list
 *
 * Return: 0 on success
 */
alias_t *alias_list(void)
{
	alias_t *head;

	head = NULL;

	return (head);
}

/**
 * add_node_alias - builtin func to set alias
 * @head: head of alias list
 * @alias: alias ot add
 * @command: actual command equivalent to alias
 *
 * Return: 0 on success
 */

alias_t *add_node_alias(alias_t **head, char *alias, char *command)
{
	alias_t *new_node, *temp;

	new_node = malloc(sizeof(alias_t));
	if (new_node == NULL)
		return (NULL);

	new_node->alias = _str_dupp(alias);
	new_node->command = _str_dupp(command);
	new_node->next = NULL;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;

		while (temp->next)
			temp = temp->next;

		temp->next = new_node;
	}

	return (new_node);
}

/**
 * modify_node_alias - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */


int modify_node_alias(alias_t **head, char *new_var, char *new_val)
{
	alias_t *temp;

	temp = *head;

	while (temp)
	{
		if (_strg_com_pare(temp->alias, new_var) == 0)
		{
			free(temp->command);
			temp->command = _str_dupp(new_val);

			return (EX_IT_SUC_CESS);
		}
		temp = temp->next;
	}

	return (EX_IT_FAI_LURE);
}


/**
 * remove_node_alias - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int remove_node_alias(alias_t **head, char *var)
{
	alias_t *copy_head = *head, *temp = *head;

	if (head == NULL)
		return (EX_IT_FAI_LURE);
	copy_head = NULL;
	while (temp)
	{
		if (_strg_com_pare(temp->alias, var) == 0)
		{
			if (copy_head)
				copy_head->next = temp->next;
			else
				*head = temp->next;

			free(temp->alias);
			free(temp->command);
			free(temp);

			return (EX_IT_SUC_CESS);
		}
		copy_head = temp;
		temp = temp->next;
	}

	return (EX_IT_FAI_LURE);
}


/**
 * write_alias - function to write alias list to stdout for testing
 * @head: head of alias list
 *
 * Return: chars written
 */
int write_alias(alias_t *head)
{
	int i = 0;
	alias_t *temp = head;

	while (temp)
	{
		write(STDOUT_FILENO, temp->alias, _str_length(temp->alias));
	    write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, temp->command, _str_length(temp->command));
	    write(STDOUT_FILENO, "\"\n", 2);

		temp = temp->next;
		i++;

	}

	return (i);
}
