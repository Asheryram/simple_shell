#include "shell.h"

/**
 * perm_ali_as - saves alias definitions to  file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int perm_ali_as(arg_in_ven_tory_t *arginv)
{
	alias_t *tmp = arginv->alias;
	char *file, *buffer;
	int fd;

	file = arginv->alias_file;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	close(fd);

	while (tmp)
	{
		buffer = (char *)safe_malloc(_str_length(tmp->alias) + _str_length(tmp->command)
									 + 4);
		_str_co_py(buffer, tmp->alias);
		_str_categ(buffer, ":");
		_str_categ(buffer, tmp->command);
		_str_categ(buffer, "\n");
		append_text_to_file(file, buffer);
		tmp = tmp->next;
		free(buffer);
	}

	return (0);
}

/**
 * up_load_al_ias - loads alias definitions from file
 * @arginv: arguments inventory
 *
 * Return: 0 success, 1 failure
 */
int up_load_al_ias(arg_in_ven_tory_t *arginv)
{
	char *file, *buffer, *val;
	int fd;
	ssize_t count;
	size_t sz = BU_FFER_SIZE;

	file = arginv->alias_file;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (1);
	}
	buffer = (char *)safe_malloc(sz);
	while ((count = _read_line(fd, &buffer, &sz)) != 0)
	{
		while (buffer[count - 1] == '\n')
			buffer[count - 1] = '\0';
		val = buffer;
		while (*val && *val != ':')
			val++;
		if (!*val)
			break;
		*(val++) = '\0';
		add_node_alias(&arginv->alias, buffer, val);
	}
	free(buffer);
	close(fd);
	return (0);
}

/**
 * fetch_node_alias - fetches a node of a given alias
 * @head: head of list
 * @var: alias to match of the node to fetch
 *
 * Return: fetched node or NULL
 */
alias_t *fetch_node_alias(alias_t *head, char *var)
{
	alias_t *tmp;

	tmp = head;

	while (tmp != NULL)
	{
		if (_strg_com_pare(tmp->alias, var) == 0)
			return (tmp);

		tmp = tmp->next;
	}

	return (NULL);
}
