#include "shell.h"

/**
 * get_variable - Find a variable in the list.
 * @name: The name of the variable to find.
 * @head: The head of the list.
 * Return: A pointer to the variable if found, otherwise NULL.
 */
list_path *get_variable(char *name, list_path *head)
{
	while (head)
	{
		if (_varcmp(name, head->path))
			return (head);
		head = head->next;
	}

	return (NULL);
}
/**
 * _varcmp - Compare a variable.
 * @var_name: The variable name to compare.
 * @full_var: The full variable string.
 * Return: 0 if the names match, -1 if not.
 */
int _varcmp(char *var_name, char *full_var)
{
	int i;

	for (i = 0; var_name[i]; i++)
	{
		if (full_var[i])
			if (var_name[i] - full_var[i] != 0)
				return (-1);
	}
	if (full_var[i] == '=')
		return (0);

	return (-1);
}

/**
 * num_to_char - Convert an integer to a char.
 * @num: The integer to convert.
 * Return: The integer as a char.
 */
char *num_to_char(int num)
{
	int c = 0, tmp = num;
	char *cp_num;

	if (num == 0)
	{
		c = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			c++;
		}
	}

	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[c] = '\0';
	while (c != 0)
	{
		c--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}

/**
 * char_count_piped - Count the number of occurrences of a character.
 * @str: The input string.
 * @c: The character to count.
 * Return: The count of occurrences.
 */
unsigned int char_count_piped(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count + 1);
}

