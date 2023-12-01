#include "main.h"

/**
 * _strncpy - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 * @n: Variable from main
 * Return: Return dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i++] = '\0';
	}
	return (dest);
}

/**
 * _strncat - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 * @n: Variable from main
 * Return: Return dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{

	}

	for (j = 0; src[j] != '\0' && j < n; j++)
	{
		dest[i + j] = src[j];
	}
	dest[i + j] = '\0';

	return (dest);
}

/**
 * *_strchr - It is a function
 * @s: Variable from main
 * @c: Variable from main
 * Return: Return S/Null
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (*s == c)
	{
		return (s);
	}
	return (NULL);
}
