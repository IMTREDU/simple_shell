#include "main.h"

/**
 * _strcpy - It is a function
 * @dest: Variable from main
 * @src: Variable from main
 *
 * Return: Return dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 *
 * Return: Return deplicate
 */
char *_strdup(const char *str)
{
	int length = 0;
	int i;
	const char *temp = str;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*temp++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));

	if (ret == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
		ret[i] = str[i];

	return (ret);
}

/**
 *_puts - It is a function
 *@str: Variable from main
 *
 * Return: Void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - prints the character 'c' to the standard output (stdout)
 * @c: The character to be printed
 *
 * Return: On success 1.
 *
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
