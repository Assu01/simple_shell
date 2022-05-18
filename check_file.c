#include "main.h"
/**
* check_in_path - check if file exist in some PATH dir
* @filename: file  checked for existence
* Return: on success -> absolute file path string
*        on failuere -> NULL
*/
char *check_in_path(char *filename)
{
	char *p;
	struct stat sb;
	int status = 0;
	filep *head, *current;

	head = gethead();
	current = head;
	while (current && current->path)
	{
		p = get_full_path(filename, current->path);
		if (p == NULL)
		{
			free_list(head);
			return (NULL);
		}
		status = stat(p, &sb);
		if (status == 0)
		{
			free_list(head);
			return (p);
		}
		current = current->next;
		free(p);

	}
	free_list(head);
	return (NULL);
}
/**
* check_in_cwd - check file existence in current workind dir
* @filename: file to be checked
* Return: absolute file path on success or NULL on failure
*/
char  *check_in_cwd(char *filename)
{
	char *path;

	path = get_path_in_cwd(filename);
	if (access(path, F_OK | R_OK | W_OK | X_OK) == 0)
	{
		return (path);
	}
	else
	{
		free(path);
		return (NULL);
	}
}
/**
* get_full_path - concatenate filename and dir to get file path
* @filename: file name
* @homedir: directory
* Return: full path string
*/
char *get_full_path(char *filename, char *homedir)
{
	char *path;
	size_t i = 0, j = 0, len;

	if (filename == NULL)
		return (NULL);
	len = _strlen(filename) + _strlen(homedir);
	path = malloc(sizeof(char) * len);
	if (path == NULL)
		return (NULL);
	_memset(path, len);
	while (homedir[i])
	{
		path[i] = homedir[i];
		i++;
	}
	path[i] = '/';
	i++;
	while (filename[j])
	{
		path[i] = filename[j];
		i++;
		j++;
	}
	return (path);
}
