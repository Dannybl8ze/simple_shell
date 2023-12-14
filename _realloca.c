#include "shell.h"

/**
 *store_set: store memory block with a constant byte.
 *
 *@s: pointer to the areaof the memory.
 *
 *@b: byte allocated to fill the pointer *s with.
 *
 *@n: amount of bytes available to be filled.
 *
 *Return: (s) a pointer to the allocated memory area s
 */
char *store_set(char *s, char j, unsigned int m)
{
	unsigned int q;

	for (q = 0; q < m; q++)
		s[q] = j;
	return (s);
}

/**
 *
 * free_s: it frees string of strings
 *
 * @pp: the string of strings.
 *
 */
void free_s(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloca - this reallocates a block of memory.
 *
 * @ptr: a pointer to the previous malloc  block.
 *
 * @old_size: byte-size of previous block.
 *
 * @new_size: byte-size of new blocks.
 *
 * Return: pointer to the previous block named.
 */
void *_realloca(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
