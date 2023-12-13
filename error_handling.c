#include "main.h"

/**
 * _erratoi - Converts a string to an int
 * @s: Converted string
 * Return: 0 if no numbers in string ,else -1
 *
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Displays an error message
 * @info: Parameter and return info struct.
 * @estr: String containing the specified error type.
 * Return: 0 if no errors, -1 on error.
 *
 */
void print_error(Commandinfo_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Outputs a decimal (integer) number in base 10.
 * @input:  The input number
 * @fd: The file descriptor for output
 *
 * Return: Number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to its string representation
 * @num: Number to convert
 * @base: Base for the conversion
 * @flags: Argument flags
 *
 * Return: String representation of the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char *array = (flags & 1) ? "0123456789abcdef" : "0123456789ABCDEF";
	char *ptr = &buffer[49];
	char sign = 0;
	unsigned long n = (num < 0 && !(flags & 2)) ? (sign = '-', -num) : num;

	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0' in a string.
 * @buf: Address of the string to modify
 *
 * Return: Always returns 0
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
