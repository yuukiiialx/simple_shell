#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
/**
 * getline_custom - A custom implementation of the getline function.
 * @line: A pointer to the buffer where the line will be stored.
 * @line_len: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * This function reads a line from the input stream and stores it in the buffer
 * pointed to by line. If the buffer is too small, it will be reallocated.
 *
 * Return: 0 on success, -1 on failure.
 */
ssize_t getline_custom(char **line, size_t *line_length,
		__attribute__((unused)) FILE * stream)
{
	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 128; /* Maximum expected line length */
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * custom_getline - A custom implementation of the getline function.
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * This function reads a line from the input stream and stores it in the buff
 * pointed to by lineptr. If the buffer is too small, it will be reallocated.
 *
 * Return: The number of characters read on success, -1 on failure.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t nread;
	char *line, *ptr;
	size_t size;

	getline_custom(lineptr, n, stream);
	ptr = *lineptr;
	size = *n;
	
	while (1)
	{
		nread = read(STDIN_FILENO, ptr, size);
		if (nread == -1)
			return (-1);
		else if (nread == 0)
			break;
		ptr += nread;
		size -= nread;
		
		if (size == 0)
		{
			size = *n * 2;
			line = malloc(sizeof(char) * size);
			if (line == NULL)
				return (-1);
			*lineptr = buff;
			ptr = *lineptr + (*n - size);
			*n = size;
		}
		if (*(ptr - 1) == '\n')
			break;
	}
	if (ptr == *lineptr)
		return (-1);
	*ptr = '\0';
	return (ptr - *lineptr);
}


