#include "main.h"

/**
 * _strlen - It is a function
 * @s: Variable from main
 *
 * Return: Return string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - It is a function
 * @s1: Variable from main
 * @s2: Variable from main
 *
 * Return: Return s1 - s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: the string to search within
 * @needle: the substring to find
 *
 * Return: the address of the next character in haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle && (*needle++ == *haystack++))
		;
	return (*needle ? NULL : (char *)haystack);
}

/**
 * _strcat - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 *
 * Return: Return ret
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
