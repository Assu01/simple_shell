#include "main.h"
/**
* free_list -free linked list
* @head: head pointer
*/
void free_list(filep *head)
{
	filep *current = head;

	while (head)
	{
		current = head->next;
		free(head->path);
		free(head);
		head = current;
	}
}
/**
 * set_next - set next node
 * @p: path
 * @i: current index in string p
 * @current: current Node
 * Return: 1 if failed 0 on success
 */
int set_next(char *p, size_t i, filep  *current)
{
	size_t len, k;
	filep *head = current;

	while (p[i])
	{
		if (p[i] == ':')
		{
			len = len_from_to(p, i + 1, ':');
			current->next = malloc(sizeof(filep));
			if (current->next == NULL)
			{
				free_list(head);
				return (1);
			}
			current->path  = malloc(sizeof(char) * (len + 1));
			if (current->path == NULL)
			{
				free_list(head);
				return (1);
			}
			_memset(current->path, len + 1);
			k = ++i;
			while (p[i] != ':' && p[i])
			{
				(current->path)[i - k] = p[i];
				i++;
			}
			if (p[i] ==  '\0')
			{
				free(current->next);
				current->next = NULL;
			}
			else
				current = current->next;
		}
	}
	return (0);
}
/**
* gethead - get head of linked list
* Return: head pointer
*/
filep *gethead()
{
	char *p;
	filep *head, *current;
	size_t i = 0, len = 0;

	p = _getenv("PATH");
	len = len_from_to(p, 0, ':');
	head = malloc(sizeof(filep));
	if (head == NULL)
		return (NULL);
	head->path = malloc(sizeof(char) * (len + 1));
	if (head->path == NULL)
	{
		free_list(head);
		return (NULL);
	}
	_memset(head->path, len + 1);
	i =  0;
	while (p[i] != ':' && p[i])
	{
		(head->path)[i] = p[i];
		i++;
	}
	current = malloc(sizeof(filep));
	if (current == NULL)
	{
		free_list(head);
		return (NULL);
	}
	head->next = current;
	if (set_next(p, i, current))
	{
		free_list(head);
		return (NULL);
	}
	return (head);
}
