#include "shell.h"

/**
 * get_commands - Get commands based on the mode.
 * @mode: The execution mode.
 * @file_name: The file name if in non-interactive mode.
 * @program_name: The name of the program.
 * Return: An array of commands.
 */
char **get_commands(int mode, char *file_name, char *program_name)
{
	char **lines = NULL;

	if (mode == NON_INTERACTIVE_PIPED)
	{
		lines = piped_non_interactive();
		if (!lines)
			exit(0);
	}
	else if (mode == NON_INTERACTIVE_FILE)
	{
		lines = file_non_interactive(file_name, program_name);
		if (!lines)
			exit(0);
	}
	return (lines);
}


/**
 * piped_non_interactive - Get commands from
 *			non-interactive mode with pipes.
 * Return: An array of commands.
 */
char **piped_non_interactive()
{
	char b[2048], *text = NULL, **lines = NULL;
	ssize_t bytesRead;
	size_t totalchar = 0;
	int i, flag = 0;

	while ((bytesRead = read(STDIN_FILENO, b, 2048)) > 0)
	{
		totalchar += bytesRead;
	}
	if (bytesRead == -1)
	{
		perror("read");
		exit(ERROR);
	}
	if (totalchar > 2048)
	{
		b[2048 - 1] = '\0';
	}
	else
	{
		b[totalchar - 1] = '\0';
	}

	for (i = 0; b[i]; i++)
	{
		if (b[i] != ' ' && b[i] != '\n' && b[i] != '\t'
						&& b[i] != '\r' && b[i] != '\a')
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	totalchar = _strlen(b);
	text = (char *)malloc((totalchar + 1) * sizeof(char));
	if (text != NULL)
	{
		_strcpy(text, b);
		text[totalchar] = '\0';
		lines = text_to_vector(text);
	}
	return (lines);
}

/**
 * text_to_vector - Split text into an array of commands.
 * @text: The input text.
 * Return: An array of commands.
 */
char **text_to_vector(char *text)
{
	char *token, *cmd;
	char **lines = NULL;
	int i = 0;
	unsigned int c_count = 0;

	c_count = char_count_piped(text, '\n');
	lines = (char **)malloc((c_count + 1) * sizeof(char *));
	token = _strtok(text, "\n");
	cmd = _strdup(token);
	lines[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, "\n");
		if (token != NULL)
		{
			cmd = _strdup(token);
			lines[i++] = cmd;
		}
	}
	free(text);
	lines[i] = NULL;
	return (lines);
}
/**
 * file_non_interactive - Get commands from a non-interactive file
 * @file_name: The name of the file.
 * @program_name: The name of the program.
 * Return: An array of commands.
 */
char **file_non_interactive(char *file_name, char *program_name)
{
	struct stat fileStat;
	char *text, **lines;
	int file_descriptor;
	size_t letters;

	if (stat(file_name, &fileStat) != -1)
	{
		if (S_ISREG(fileStat.st_mode))
		{
			file_descriptor = open(file_name, O_RDONLY);
			if (file_descriptor  == -1)
				exit(ERROR);
			if (fileStat.st_size == 0)
				exit(0);
			text = malloc((fileStat.st_size + 1) * sizeof(char));
			if (!text)
				return (NULL);
			letters = read(file_descriptor, text, fileStat.st_size);
			if ((int) letters == -1)
			{
				perror("read");
			}
			close(file_descriptor);

			text[letters - 1] = '\0';
			if (text)
				lines = text_to_vector(text);
			return (lines);
		}
		else
			exit(0);
	}
	else
	{
		print_cant_open(program_name, 0, file_name);
		exit(127);
	}
	return (NULL);
}

