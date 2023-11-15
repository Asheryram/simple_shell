#include "shell.h"


/**
 * put_node_env_ment_ment - checks to see if node exists, and modifies it if so.
 * @head: beginning of linked list
 * @new_var: variable to modify
 * @new_val: new string to be modified to found node
 *
 * Return: pointer to new node or NULL if fail
 */
int put_node_env_ment_ment(env_ment **head, char *new_var, char *new_val)
{
	env_ment *temp;

	temp = *head;

	while (temp)
	{
		if (_strg_com_pare(temp->var, new_var) == 0)
		{
			free(temp->val);
			temp->val = _str_dupp(new_val);

			return (EX_IT_SUC_CESS);
		}
		temp = temp->next;
	}

	return (EXT_FAILURE);
}

/**
 * add_node_env_ment_ment - adds new node to end of linked list
 * @head: beginning of linked list
 * @var: variable to be added
 * @val: value to be added
 *
 * Return: pointer to new node
 */
env_ment *add_node_env_ment_ment(env_ment **head, char *var, char *val)
{
	env_ment *new_node, *temp;

	new_node = safe_malloc(sizeof(env_ment));

	new_node->var = _str_dupp(var);
	new_node->val = _str_dupp(val);
	new_node->next = NULL;

	if (!*head)
	{
		*head = new_node;
	}
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
 * fetch_node - fetches a node of a given var
 * @head: head of list
 * @var: value to match of the node to fetch
 *
 * Return: fetched node or head
 */
env_ment *fetch_node(env_ment *head, char *var)
{
	env_ment *tmp;

	tmp = head;

	while (tmp != NULL)
	{
		if (_strg_com_pare(tmp->var, var) == 0)
			return (tmp);

		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * del_node_env_ment_ment - removes node from linked list
 * @head: beginning of linked list
 * @var: var of node to be removed from linked list
 *
 * Return: pointer to new node or NULL
 */
int del_node_env_ment_ment(env_ment **head, char *var)
{
	env_ment *copy_head = *head, *temp = *head;

	if (head == NULL)
		return (EXT_FAILURE);
	copy_head = NULL;
	while (temp)
	{
		if (_strg_com_pare(temp->var, var) == 0)
		{
			if (copy_head)
				copy_head->next = temp->next;
			else
				*head = temp->next;

			free(temp->var);
			free(temp->val);
			free(temp);

			return (EX_IT_SUC_CESS);
		}
		copy_head = temp;
		temp = temp->next;
	}

	return (EXT_FAILURE);
}