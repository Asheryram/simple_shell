#include "shell.h"

/**
 * _is_t_space - checks if input char is a space character
 * @c: input character
 *
 * Return: 1 on success, 0 on failure
 */
char _is_t_space(char c)
{
	int i;

	switch (c)
	{
	case ' ': case '\t': case '\n':
	case '\v': case '\f': case '\r':
		i = 1;
		break;
	default:
		i = 0;
		break;
	}

	return (i);
}

/**
 * _a_to_oi - returns integer values from string
 * @s: input string
 *
 * Return: will return integer
 */
int _a_to_oi(char *s)
{
	int result = 0, sign = 0, c;

	for (c = 0; s[c] != '\0'; c++)
	{
		if (s[c] == '-')
			sign++;
		if (s[c] > 47 && s[c] < 58)
		{
			while (s[c] > 47 && s[c] < 58)
				result = result * 10 - (s[c++] - 48);
			break;
		}
	}
	return (result *= sign % 2 == 0 ? -1 : 1);
}

/**
 * _process_err - custom perror
 * @string: input error string to write to stderr
 *
 * Return: void
 */
void _process_err(char *string)
{
	unsigned int len;

	len = _str_length(string);

	write(STDERR_FILENO, string, len);
}

/**
 * _chg_mem_loc - shifting an array
 * @dest: dest
 * @src: source
 * @n: bytes to move
 */
void _chg_mem_loc(void *dest, void *src, size_t n)
{
	char *copy_source, *copy_dest, *temp;
	size_t i;

	copy_source = (char *)src;
	copy_dest = (char *)dest;
	temp = malloc(sizeof(char) * 1024);

	for (i = 0; i < n; i++)
		temp[i] = copy_source[i];

	for (i = 0; i < n; i++)
		copy_dest[i] = temp[i];
	free(temp);
}

/**
 * is_unsgn_int - checks if input string is unsigned int
 * @num: the input number
 * Return: TRUE_THY or FALSE_THY
 */
int is_unsgn_int(char *num)
{
	int i = 0;

	while (num[i])
	{
		if (num[i] > 47 && num[i] < 58)
			i++;
		else if (num[i] == 45 && i == 0)
			return (FALSE_THY);
		else
			return (FALSE_THY);
	}

	return (TRUE_THY);
}
