#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

/**
 * struct ListNode - Represents a node in a singly linked list
 * @data: The numerical data field of the node
 * @text: A string associated with the node
 */
typedef struct Node
{
	int data;
	char *text;
	struct Node *nextNode;
} ListNode_t;

/**
 * struct CommandInfo - Represents information related to a command execution
 * @argument: The main argument for the command
 * @arguments_array: Array of arguments for the command
 * @executable_path: Path to the executable for the command
 * @argument_count: Number of arguments in the command
 * @line_number: Line number associated with the command
 * @error_number: Error code for exit() calls
 * @line_count_flag: Flag to indicate whether to count this line of input
 * @filename: The program filename
 * @environment_variables: Custom modified copy of the environment variables
 * @environment_changed: Flag indicating if the environment was changed
 * @execution_status: The return status of the last executed command
 * @command_buffer: Pointer to a chain buffer for storing commands (memory management)
 * @command_buffer_type: Type of command in the buffer (CMD_type ||, &&, ;)
 * @file_descriptor: File descriptor from which to read line input
 * @history_count: Count of the history line number
 * @environment: Linked list representing the local copy of the environment (environ)
 * @command_alias: Linked list representing command aliases
 * @command_history: Linked list representing the history of executed commands
 */
typedef struct CommandInfo
{
	char *argument;
	char **arguments_array;
	char *executable_path;
	int argument_count;
	unsigned int line_number;
	int error_number;
	int line_count_flag;
	char *filename;
	char **environment_variables;
	int environment_changed;
	int execution_status;
	char **command_buffer;
	int command_buffer_type;
	int file_descriptor;
	int history_count;
	ListNode_t *environment;
	ListNode_t *command_alias;
	ListNode_t *command_history;
} CommandInfo_t;

/**
 * struct BuiltinCommand - Represents a built-in command with its related function
 * @type: The built-in command string identifier
 * @func: Pointer to the associated function for the built-in command
 */
typedef struct BuiltinCommand
{
	char *type;
	int (*func)(CommandInfo_t *);
} BuiltinCommandTable_t;

/* StringFunctions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *starts_with_prefix(const char *haystack, const char *needle);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
void _puts(char *str);
int _putchar(char c);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

#endif /* MAIN_H */
