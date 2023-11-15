#include "shell.h"
/**
 * handle_comments - Remove comments from the input line.
 * @line: The input line.
 */
void handle_comments(char *line)
{
	int len = _strlen(line);
	int x = 0;
	int start = 0;

	for (x = 0; x < len; x++)
	{
		if (line[x] == ' ')
		{
			start = 0;
		}
		else if (line[x] == '#')
		{
			if (!start)
			{
				line[x] = '\0';
				break;
			}
		}
		else
		{
			start = 1;
		}
	}
}

/**
 * change_directory - Change the current working directory.
 * @line_vector: The array of command arguments.
 * @argv: The array of command line arguments.
 * Return: 0 on success, 1 on failure.
 */
int change_directory(char **line_vector, char **argv)
{
	char *dir = line_vector[1];
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (dir == NULL || _strcmp(dir, "~") == 0)
		dir = _getenv("HOME");
	else if (_strcmp(dir, "-") == 0)
		dir = _getenv("OLDPWD");
	if (chdir(dir) == -1)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": 1", 3);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, line_vector[0], _strlen(line_vector[0]));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, line_vector[1], _strlen(line_vector[1]));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	else
	{
		setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");
			return (1);
		}
	}
	return (0);
}


/**
 * free_all_resources - Free dynamically allocated resources.
 * @lines: Array of lines.
 * @counter: Line counter.
 * @env: List of environment variables.
 * @current: Current working directory.
 * @line: The input line.
 * @line_vector: Array of command arguments.
 */
void free_all_resources(char **lines, int counter, list_path *env,
		list_path *current, char *line, char **line_vector)
{
	if (lines)
	{
		free(lines[counter]);
		if (lines)
			free(lines);
	}
	free_list(env);
	free_list(current);
	free_l_v(line, line_vector);
}

