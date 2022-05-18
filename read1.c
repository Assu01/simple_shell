#include "main.h"
/**
* _strcpy_index - copy chars from src to dest starting from start_index
* @src: source string
* @dest: destination string
* @start_index: index of dest where copy starts
*/
void _strcpy_index(char *src, char *dest, size_t start_index)
{
	size_t j = 0;

	while (src[j])
	{
		dest[start_index + j] = src[j];
		j++;
	}
}
/**
* _readline - read char form terminal @ 1024 buffer
* Return: pointer to all chars read stored as single string
*/
char *_readline(void)
{
	ssize_t n, size = 0;
	char buf[1024];
	char  *cp, *cpp;

	_memset(buf, 1024);
	n = read(STDIN_FILENO, buf, 1024);
	if (n == 0 || (n < 1024 && buf[n - 1] != '\n'))
	{
		_printf("\n");
		return (NULL);
	}
	size = size + n;
	cp = malloc(sizeof(char) * size);
	_memset(cp, size);
	_strcpy(buf, cp);
	while (buf[n - 1] != '\n')
	{
		_memset(buf, 1024);
		n = read(STDIN_FILENO, buf, 5);
		if ((n < 1024 && buf[n - 1] != '\n') || n == 0)
		{
			_printf("\n");
			free(cp);
			return (NULL);
		}
		cpp = cp;
		size = size + n;
		cp = malloc(sizeof(char) * size);
		if (cp == NULL)
		{
			free(cpp);
			return (NULL);
		}
		_memset(cp, size);
		_strcpy(cpp, cp);
		_strcpy_index(buf, cp, size - n);
		free(cpp);
	}
	cp[size - 1] = '\0';
	return (cp);
}
