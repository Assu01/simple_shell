#include "main.h"
/**
* _getcwd - get current working directory
* Return: cwd string
*/
char *_getcwd()
{
	char *cwd = NULL;
	char *to_be_free;
	int size  =  100;

	cwd = getcwd(cwd, size);
	to_be_free = cwd;
	while (cwd == NULL)
	{
		size = size * 2;
		cwd = getcwd(cwd, size);
		free(to_be_free);
	}
	return (cwd);
}
/**
* get_path_in_cwd - get file path in cwd
* @filename: file whose full path required
* Return: full file path for filename in current directory
*/
char *get_path_in_cwd(char *filename)
{
	int len = 0, j = 0;
	char *cwd, *path;

	cwd = _getcwd();
	if (cwd == NULL)
		return (NULL);
	while (cwd[len])
		len++;
	while (filename[j])
	{
		j++;
		len++;
	}
	path = malloc(sizeof(char) * (len + 1));
	if (path == NULL)
		return (NULL);
	_memset(path, len + 1);
	len = 0;
	j = 0;
	while (cwd[len])
	{
		path[len] = cwd[len];
		len++;
	}
	path[len] = '/';
	len++;
	while (filename[j])
	{
		path[len + j] = filename[j];
		j++;
	}
	free(cwd);
	return (path);
}
