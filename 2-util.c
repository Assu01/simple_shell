#include "main.h"
/**
* free_ptr -free poiner
*  @ptr: ptr to be freed
*/
void free_ptr(char *ptr)
{
	if (ptr)
		free(ptr);
}
/**
* free_dblptr - free two ptr
* @argv: dbl ptr
* @cmd: single ptr
*/
void free_dblptr(char **argv, char *cmd)
{
	int j = 0;

	if (cmd)
		free(cmd);
	while (argv && argv[j])
	{
		if (argv[j])
			free(argv[j]);
		j++;
	}
	if (argv)
		free(argv);
}
