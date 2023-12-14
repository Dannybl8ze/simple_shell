#include "shell.h"

/**
 * free_b: this frees a pointer and NULLs the address.
 *
 * @ptr: the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_b(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
