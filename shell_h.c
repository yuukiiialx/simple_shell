#include "shell.h"

/**
 * check_mode - Determine the shell mode.
 * @argc: Number of command line arguments.
 * Return: Mode of the shell.
 */
int check_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (isatty(STDIN_FILENO) && argc == 1)
		return (INTERACTIVE);
	if ((!isatty(STDIN_FILENO) && argc == 1))
		return (NON_INTERACTIVE_PIPED);
	if ((argc >= 1))
		return (NON_INTERACTIVE_FILE);

	return (ERROR);
}

/**
 * is_exit - Handle the "exit" command.
 * @line: Input command line.
 * @line_vector: Parsed command line arguments.
 * @current: Current working directory.
 * @program_name: Name of the shell program.
 * @counter: Counter for the executed commands.
 * @status: Exit status to be updated.
 * @env: Shell environment variables.
 * @lines: Array of input lines.
 * Return: void
 */

void is_exit(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status, list_path *env, char **lines)
{
	int n;

	if (_strcmp(line_vector[0], "exit") == 0)
	{
		if (line_vector[1] == NULL)
		{
			free_all(lines, counter, env, current, line, line_vector);
			exit(*status);
		}
		else if (line_vector[1] != NULL)
		{
			if (_strlen(line_vector[1]) <= 9)
			{
				n = _atoi(line_vector[1]);
				if (n != -1)
				{
					free_all(lines, counter, env, current, line, line_vector);
					exit(n);
				}
				else
				{
					*status = EXIT_ERROR;
					print_error(program_name, counter, line_vector[1], EXIT_ERROR);
				}
			}
			else
			{
				*status = EXIT_ERROR;
				print_error(program_name, counter, line_vector[1], EXIT_ERROR);
			}
		}
	}
}
/**
 * _atoi - Convert a string to an integer.
 * @s: Input string.
 * Return: The converted integer.
 */
int _atoi(char *s)
{
	unsigned int n, i;
	char positive;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
		{
			return (-1);
		}
		if (((s[i] >= '0') && (s[i] <= '9')))
		{
			n = (n * 10) + (s[i] - '0');
		}
		else if (s[i] == '+')
			positive++;

		i++;
	}

	return (n);
}

/**
 * execute_command - Execute a command.
 * @path: Path to the command to execute.
 * @av: Arguments for the command.
 * @env: Shell environment variables.
 * @status: Exit status to be updated.
 * Return: void
 */

void execute_command(char *path, char **av, char **env, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, av, env) == -1)
			exit(126);
	}
	else if (pid > 0)
	{

		waitpid(pid, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}

/**
 * free_vector - Free memory allocated for a string array.
 * @argv: The string array to be freed.
 * Return: void
 */

void free_vector(char **argv)
{
	char **curr;

	if (argv == NULL)
		return;

	curr = argv;
	while (*curr != NULL)
	{
		free(*curr);
		curr++;
	}

	free(argv);
}

