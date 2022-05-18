#include "shell.h"

/**
 * _realloc - reallocates memory block
 * @ptr: pointer to original memory allocation
 * @old_size: size, in bytes, of original memory block
 * @new_size: size, in bytes, of new memory block
 *
 * Return: pointer to new memory block, null in certain edge cases
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	unsigned int copy_size, index;
	char *old_contents, *new_contents;


	if (old_size == new_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);

	if (ptr == NULL)
		return (new_ptr);

	copy_size = old_size < new_size ? old_size : new_size;
	old_contents = ptr;
	new_contents = new_ptr;

	for (index = 0; index < copy_size; index++)
		new_contents[index] = old_contents[index];

	new_ptr = new_contents;
	free(ptr);
	return (new_ptr);
}
/**
 * free_array - free an array of strings
 * @array: array to free
 */

void free_array(char **array)
{
	size_t i;

	for (i = 0; array[i] != '\0'; i++)
	{
		free(array[i]);
	}

	free(array);

}
