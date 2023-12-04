#include "main.h"

/**
 * _memset - It is a function
 * @s: Variable from main
 * @b: Variable from main
 * @n: Variable from main
 * Return: Return s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * reallocMemory - reallocates a block of memory
 * @ptr: pointer to previous block
 * @oldSize: byte size of previous block
 * @newSize: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *reallocMemory(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	if (!ptr)
	{
		return (malloc(newSize));
	}
	if (!newSize)
	{
		return (free(ptr), NULL);
	}
	if (newSize == oldSize)
	{
		return (ptr);
	}
	char *newPtr = malloc(newSize);

	if (!newPtr)
	{
		return (NULL);
	}
	for (unsigned int i = 0; i < oldSize && i < newSize; i++)
	{
		newPtr[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (newPtr);
}

/**
 * freeStringArray - frees a dynamic array of strings
 * @stringArray: array of strings
 */
void freeStringArray(char **stringArray)
{
	char **tempPointer = stringArray;

	if (!stringArray)
	{
		return ();
	}
	while (*stringArray)
	{
		free(*stringArray++);
	}
	free(tempPointer);
}
