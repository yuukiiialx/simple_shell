#include "shell.h"
/**
 * print_environment - Prints the environment variables.
 * @status: Pointer to the status variable.
 */
void print_environment(int *status)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	*status = 0;
}
/**
 * get_status - Converts an integer status to a string.
 * @n: The integer status.
 * Return: The status as a string.
 */
char *get_status(int n)
{
	char *status;

	status = num_to_char(n);
	return (status);
}


/**
 * get_process_id - Gets the process ID as a string.
 * Return: The process ID as a string.
 */
char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}
/**
 * is_built_in - Checks if a command is a built-in command.
 * @line: The command line.
 * @line_vector: The command line tokens.
 * @current: Current working directory.
 * @program_name: Name of the program.
 * @counter: Command counter.
 * @status: Pointer to the status variable.
 * @env_list: List of environment variables.
 * @lines: Command history.
 * @argv: Command line arguments.
 * Return: 0 if the command is a built-in, -1 if not.
 */
int is_built_in(char *line, char **line_vector, list_path *current,
	char *program_name, int counter, int *status, list_path *env_list,
	char **lines, char **argv)
{
	int i, n = -1;
	char *built_in[] = {"env", "exit", "cd", "setenv", "unsetenv"};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(built_in[i], line_vector[0]) == 0)
		{
			n = i;
			break;
		}
	}
	if (n == -1)
		return (n);

	switch (n)
	{
		case 0:
			print_environment(status);
			break;
		case 1:
			is_exit(line, line_vector, current, program_name,
					counter, status, env_list, lines);
			break;
		case 2:
			_cd(line_vector, argv);
			break;
		case 3:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		case 4:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		default:
			return (-1);
	}
	return (0);
}
/**
 * _setenv - Sets an environment variable.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 * @env_list: List of environment variables.
 */
void _setenv(char *name, char *value, list_path *env_list)
{
	list_path *var;
	char *full_var;
	int count;

	count = _strlen(name) + _strlen(value) + 2;
	full_var = malloc(count);
	if (full_var == NULL)
	{
		perror("setenv ERROR");
	}
	full_var = _strcpy(full_var, name);
	full_var[_strlen(name)] = '=';
	full_var[_strlen(name) + 1] = '\0';
	full_var = _strcat(full_var, value);
	full_var[count - 1] = '\0';
	var = get_variable(name, env_list);

	if (var == 0)
	{
		free(var->path);
		var->path = full_var;
		var->len = _strlen(full_var);
	}
	else
	{
		add_node(&env_list, full_var);
		var->len = _strlen(full_var);
	}

	print_list(env_list);

}
