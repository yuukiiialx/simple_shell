#include "shell.h"
/**
 * add_node - Add a node to the path list.
 * @head: A pointer to the head of the path list.
 * @path: The path to add to the list.
 * Return: A pointer to the newly added node.
 */

list_path *add_node(list_path **head, char *path)
{
	char *s_cpy;
	list_path *l;

	l = malloc(sizeof(list_path));
	if (l == NULL)
		return (NULL);

	if (path)
	{
		s_cpy = _strdup(path);
		if (s_cpy == NULL)
		{
			free(l);
			return (NULL);
		}
		l->path = s_cpy;
		l->len = _strlen(s_cpy);
	}
	else
	{
		l->path = NULL;
		l->len = 0;
	}
	l->next = (*head);
	*head = l;
	return (l);
}

/**
 * free_list - Frees a list of paths.
 * @head: Pointer to the head of the path list.
 */
void free_list(list_path *head)
{

	if (head == NULL)
	{
		return;
	}
	free_list(head->next);
	if (head->path)
		free(head->path);
	free(head);
}

/**
 * set_all_paths_to_list - Set paths from the PATH environment variable to a list.
 * Return: A list of paths.
 */
list_path *set_all_paths_to_list()
{
	char *path_variable, *path_var_cpy, *token;
	list_path *paths_list;

	paths_list = NULL;

	path_variable = _getenv("PATH");
	if (path_variable == NULL)
		return (NULL);

	path_var_cpy = _strdup(path_variable);
	if (path_var_cpy == NULL)
		return (NULL); /*can't cpy*/

	token = _strtok(path_var_cpy, ":");
	while (token != NULL)
	{
		add_node(&paths_list, token);
		token = _strtok(NULL, ":");
	}
	free(path_var_cpy);
	return (paths_list); /*does not have access*/
}
/**
 * set_all_vector_to_list - Set environment variables to a list.
 * Return: A list of environment variables.
 */
list_path *set_all_vector_to_list()
{
	char *path_var_cpy;
	list_path *paths_list;
	int i = 0;

	paths_list = NULL;

	if (environ == NULL)
		return (NULL);
	while (environ[i])
	{
		path_var_cpy = environ[i];
		if (path_var_cpy == NULL)
			return (NULL);
		add_node(&paths_list, path_var_cpy);
		i++;
	}
	return (paths_list); /*does not have access*/
}

/**
 * check_access - Find an executable file in the paths.
 * @line_av_1: The command to search for.
 * @current: The list of paths to search in.
 * Return: The full path of the executable if found, NULL otherwise.
 */

char *check_access(char *line_av_1, list_path *current)
{
	char *full_path;
	int found = 0, len;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		len = _strlen(current->path) + _strlen(line_av_1) + 2;
		if (len > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(len * sizeof(char));
		_strcpy(full_path, current->path);
		_strcat(full_path, "/");
		_strcat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (found)
		return (full_path);

	else
		return (NULL);
}

