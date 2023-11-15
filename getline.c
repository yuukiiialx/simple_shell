#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
/**
 * _getlineHelper - A custom implementation of the getline function.
 * @lineptr: A pointer to the buffer where the line will be stored.
 * @n: A pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * This function reads a line from the input stream
 * pointed to by line. If the buffer is too small.
 *
 * Return: 0 on success, -1 on failure.
 */
ssize_t _getlineHelper(char **lineptr, size_t *n,
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
 * _getline - .
 * @lineptr: .
 * @n: .
 * @stream: .
 * Return: .
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t nread;
	char *buff, *ptr;
	size_t size;

	_getlineHelper(lineptr, n, stream);
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
			buff = malloc(sizeof(char) * size);
			if (buff == NULL)
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


