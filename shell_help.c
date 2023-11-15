#include "shell.h"

/**
 * checkShellMode - Determine the shell mode.
 * @argc: Number of command line arguments.
 * Return: Mode of the shell.
 */
int checkShellMode(int argc)
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
 * handleExit - Handle the "exit" command.
 * @line: Input command line.
 * @lineArgs: Parsed command line arguments.
 * @currentPath: Current working directory.
 * @programName: Name of the shell program.
 * @commandCounter: Counter for the executed commands.
 * @exitStatus: Exit status to be updated.
 * @environment: Shell environment variables.
 * @inputLines: Array of input lines.
 * Return: void
 */

void handleExit(char *line, char **lineArgs, list_path *currentPath,
                char *programName, int commandCounter, int *exitStatus,
                list_path *environment, char **inputLines)
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
 * runCommand - Execute a command.
 * @pathToCommand: Path to the command to execute.
 * @commandArgs: Arguments for the command.
 * @environmentVariables: Shell environment variables.
 * @exitStatus: Exit status to be updated.
 * Return: void
 */

void runCommand(char *path, char **av, char **env, int *status)
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
 * @array: The string array to be freed.
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

