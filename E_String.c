#include "main.h"

/**
 * customPrintString - prints an input string
 * @inputStr: the string to be printed
 *
 * Return: Nothing
 */
void customPrintString(char *inputStr)
{
	int index = 0;

	if (!inputStr)
	{
		return ();
	}
	while (inputStr[index] != '\0')
	{
		customPrintChar(inputStr[index]);
		index++;
	}
}

/**
 * customPrintCharToStderr - writes the character to stderr
 * @character: The character to print
 *
 * Return: On success 1, On error -1
 */
int customPrintCharToStderr(char character)
{
	static int index;
	static char buffer[1024];

	if (character == '\0' || index >= sizeof(buffer))
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != '\0')
	{
		buffer[index++] = character;
	}
	return (1);
}

/**
 * writeToFD - writes the character to a given file descriptor
 * @character: The character to print
 * @fileDescriptor: The file descriptor to write to
 *
 * Return: On success 1, on error -1
 */
int writeToFD(char character, int fileDescriptor)
{
	static int index;
	static char buffer[1024];

	if (character == '\0' || index >= sizeof(buffer))
	{
		write(fileDescriptor, buffer, index);
		index = 0;
	}
	if (character != '\0')
	{
		buffer[index++] = character;
	}
	return (1);
}

/**
 * printStringToFD - prints an input string to a given file descriptor
 * @inputStr: the string to be printed
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int printStringToFD(char *inputStr, int fileDescriptor)
{
	int count = 0;

	if (!inputStr)
	{
		return (0);
	}
	while (*inputStr)
	{
		count += writeToFD(*inputStr++, fileDescriptor);
	}
	return (count);
}
