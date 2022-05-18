#include "main.h"
/**
* _readFromFile - read line from file
* @file: absolute file path
* Return: pointer to string containing array of read chars
*/
char *_readFromFile(char *file)
{
	ssize_t n, size = 0;
	char buf[1024];
	static char  *cp, *cpp;
	int fd = open(file, O_RDONLY);

	if (fd == -1)
		return (NULL);
	_memset(buf, 1024);
	n = read(fd, buf, 1024);
	size = size + n;
	cp = malloc(sizeof(char) * size);
	if (cp == NULL)
	{
		close(fd);
		return (NULL);
	}
	_memset(cp, size);
	_strcpy(buf, cp);
	while (n > 0)
	{
		_memset(buf, 1024);
		n = read(fd, buf, 1024);
		cpp = cp;
		size = size + n;
		cp = malloc(sizeof(char) * size);
		if (cp == NULL)
		{
			if (cpp)
				free(cpp);
			close(fd);
			return (NULL);
		}
		_memset(cp, size);
		_strcpy(cpp, cp);
		_strcpy_index(buf, cp, size - n);
		free(cpp);
	}
	cp[size - 1] = '\0';
	close(fd);
	return (cp);
}
