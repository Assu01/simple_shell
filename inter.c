#include "main.h"
/**
* _interline - read line from file
* Return: pointer to string containing array of read chars
*/
char *_interline(void)
{
	ssize_t n, size = 0;
	char buf[1024];
	char  *cp, *cpp;

	_memset(buf, 1024);
	n = read(STDIN_FILENO, buf, 1024);
	size = size + n;
	cp = malloc(sizeof(char) * size);
	if (cp == NULL)
		return (NULL);
	_memset(cp, size);
	_strcpy(buf, cp);
	while (n > 0)
	{
		_memset(buf, 1024);
		n = read(STDIN_FILENO, buf, 1024);
		cpp = cp;
		size = size + n;
		cp = malloc(sizeof(char) * size);
		if (cp == NULL)
		{
			if (cpp)
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
