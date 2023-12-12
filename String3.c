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
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}


/**
 * _strncat - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 * @n: Variable from main
 * Return: Return s
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - Locates a character in a string
 *@s: String to search
 *@c: Character to locate
 *Return: Return S/Null
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (*s == c ? s : NULL);
}
