#include "shell.h"


/**
 * link_to_poin_ter - converts linked list to double pointer
 * @head: head pointer to head of linked list
 *
 * Return: array of pointers, pointing to strings
 */
char **link_to_poin_ter(env_ment *head)
{
	int i;
	unsigned int count, len1, len2, lennew;
	char **dpointer, *var, *val, *new_val;
	env_ment *tmp;

	count = link_counts(head);
	dpointer = malloc(sizeof(char *) * (count + 1));

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		var = tmp->var;
		val = tmp->val;
		len1 = _str_length(var);
		len2 = _str_length(val);

		lennew = len1 + len2 + 2;
		new_val = safe_malloc(lennew * sizeof(char));

		_strn_cat(new_val, var, len1);
		_strn_cat(new_val, "=", 1);
		_strn_cat(new_val, val, len2);
		dpointer[i] = new_val;
		tmp = tmp->next;
		i++;
	}
	dpointer[i] = NULL;

	return (dpointer);
}




/**
 * env_list - creates a linked list of all environ variables
 *
 * Return: head (pointer to first node of linked list of environ variables)
 */
env_ment *env_list(void)
{
	int i;
	env_ment *head;
	char **variable;

	head = NULL;
	for (i = 0; environ[i] != NULL; i++)
	{
		variable = se_pa_rate_string(environ[i]);
		if (add_node_env_ment_ment(&head, variable[0], variable[1]) == NULL)
			return (NULL);
		free(variable[0]);
		free(variable[1]);
		free(variable);
	}

	return (head);
}

/**
 * link_counts - counts number of nodes in linked list
 * @head: pointer to head of linked list
 *
 * Return: number of nodes
 */
unsigned int link_counts(env_ment *head)
{
	env_ment *tmp;
	unsigned int count;

	tmp = head;
	count = 0;

	while (tmp != NULL)
	{
		tmp = tmp->next;
		count++;
	}

	return (count);
}