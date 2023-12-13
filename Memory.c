#include "main.h"

/**
 * _memset - Fills a memory area with a constant byte.
 * @s: Pointer to the memory area.
 * @b: Byte to fill *s with.
 * @n: Number of bytes to be filled.
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: String of strings.
 */
void ffree(char **pp)
{
	char **temp = pp;

	if (!pp)
		return;
	while (*pp)
	{
		free(*pp);
		pp++;
	}

	free(temp);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous dynamically allocated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

