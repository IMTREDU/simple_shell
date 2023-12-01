#include "main.h"

/**
 * _strlen - It is a function
 * @s: Variable from main
 * Return: Return string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{

	}
	return (i);
}

/**
 * _strcmp - It is a function
 * @s1: Variable from main
 * @s2: Variable from main
 * Return: Return s1 - s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

/**
 * _strcat - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 * Return: Return dest
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{

	}

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i + j] = src[j];
	}
	dest[i + j] = '\0';

	return (dest);
}

/**
 * starts_with_prefix - checks if needle starts with haystack
 * @haystack: the string to search within
 * @needle: the substring to find
 *
 * Return: the address of the next character in haystack or NULL
 */
char *starts_with_prefix(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}
