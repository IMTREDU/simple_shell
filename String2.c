#include "main.h"

/**
 * _strcpy - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 * Return: Return char
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - It is a function
 * @str: Variable from main
 * Return: Return deplicate
 */
char *_strdup(char *str)
{
	int len, i;
	char *dup;

	if (str == NULL)
	{
		return (NULL);
	}

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}

	dup = malloc((len + 1) * sizeof(char));

	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		dup[i] = str[i];
	}

	return (dup);
}

/**
 * _puts - It is a function
 * @str: Variable from main
 * Return: Return Void
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		putchar(*str);
		str++;
	}
	putchar('\n');
}

/**
 * _putchar - prints the character 'c' to the standard output (stdout)
 * @c: The character to be printed
 *
 * Return: On success 1
 */
int _putchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}
