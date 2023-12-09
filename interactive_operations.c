#include "main.h"

/**
 * exeInteractiveOperation - brief Checks if the shell is in interactive mode.
 * @info: Pointer to a 'struct address'
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int exeInteractiveOperation(Commandinfo_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 * _isalpha - check alphebetic character
 * @c: character to be checked
 * Return: 1 for alphebetic character or 0
 */

int _isalpha(int c)
{
	if ((c >= 65 && c <= 97) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}
/**
 * _atoi - It is a function
 * @s: Variable from main
 * Return: Return Void
 */
int _atoi(char *s)
{
	int sign = 1;
	int i = 0;
	unsigned int res = 0;

	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}

	res *= sign;
	return (res);
}
