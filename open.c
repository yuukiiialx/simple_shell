#include "shell.h"

/**
 * print_error - Print error messages based on the type of error.
 * @program_name: The name of the program.
 * @counter: The counter value.
 * @command: The command or message to be printed.
 * @type_of_error: The type of error (e.g., NOT_FOUND, PERMISSION_DENIED, EXIT_ERROR).
 * Return: void
 */

void print_error(char *program_name, int counter,
		char *command, int type_of_error)
{
	char *counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == EXIT_ERROR)
		write(STDERR_FILENO, "exit", 4);
	else
		write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == NOT_FOUND)
		write(STDERR_FILENO, "not found\n", 10);
	else if (type_of_error == PERMISSION_DENIED)
		write(STDERR_FILENO, "Permission denied\n", 18);
	else if (type_of_error == EXIT_ERROR)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command, _strlen(command));
		write(STDERR_FILENO, "\n", 1);
	}
	free(counter_s);
}


/**
 * print_cant_open - Print a message indicating a file can't be opened.
 * @program_name: The name of the program.
 * @counter: The counter value.
 * @file_name: The name of the file that can't be opened.
 * Return: void
 */
void print_cant_open(char *program_name, int counter, char *file_name)
{

	char *counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "Can't open ", 11);
	write(STDERR_FILENO, file_name, _strlen(file_name));
	write(STDERR_FILENO, "\n", 1);
	free(counter_s);
}

