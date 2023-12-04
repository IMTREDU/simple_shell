#include "main.h"

/**
 * splitStr - Splits a string into words,(delimiters are ignored)
 * @s: The input string to be split
 * @d: The delimiter string
 *
 * Return: A pointer to an array of strings, or NULL
 */
char **splitStr(char *s, char *d)
{
	int i, j, k, m, num = 0;
	char **r;

	if (s == NULL || s[0] == '\0')
	{
		return (NULL);
	}
	if (!d)
	{
		d = " ";
	}
	for (i = 0; s[i] != '\0'; i++)
	{
		if (!isDelim(s[i], d) && (isDelim(s[i + 1], d) || !s[i + 1]))
			num++;
	}
	if (num == 0)
	{
		return (NULL);
	}
	r = malloc((1 + num) * sizeof(char *));
	if (!r)
	{
		return (NULL);
	}
	for (i = 0, j = 0; j < num; j++)
	{
		while (isDelim(s[i], d))
			i++;
		k = 0;
		while (!isDelim(s[i + k], d) && s[i + k])
		{
			k++;
		}
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
			{
				free(r[k]);
			}
			free(r);
			return (NULL);
		}
		for (m = 0; m < k; m++)
		{
			r[j][m] = s[i++];
		}
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}

/**
 * splitStr2 - Splits a string into words
 * @s: The input string to be split
 * @d: The delimiter character
 *
 * Return: A pointer to an array of strings, or NULL
 */
char **splitStr2(char *s, char d)
{
	int i, j, k, m, num = 0;
	char **r;

	if (s == NULL || s[0] == '\0')
	{
		return (NULL);
	}
	for (i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] != d && s[i + 1] == d) ||
		(s[i] != d && !s[i + 1]) || s[i + 1] == d)
		{
			num++;
		}
	}
	if (num == 0)
	{
		return (NULL);
	}
	r = malloc((1 + num) * sizeof(char *));
	if (!r)
	{
		return (NULL);
	}
	for (i = 0, j = 0; j < num; j++)
	{
		while (s[i] == d && s[i] != d)
		{
			i++;
		}
		k = 0;
		while (s[i + k] != d && s[i + k] && s[i + k] != d)
		{
			k++;
		}
		r[j] = malloc((k + 1) * sizeof(char));
		if (!r[j])
		{
			for (k = 0; k < j; k++)
			{
				free(r[k]);
				free(r);
				return (NULL);
			}
		}
		for (m = 0; m < k; m++)
		{
			r[j][m] = s[i++];
		}
		r[j][m] = 0;
	}
	r[j] = NULL;
	return (r);
}
