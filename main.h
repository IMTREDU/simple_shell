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

extern char **environ;

/**
 * struct Node - Represents a node in a singly linked list
 * @num: The numerical data field of the node
 * @str: A string associated with the node
 * @next: Pointer points to the next Node
 */
typedef struct Node
{
	int num;
	char *str;
	struct Node *next;
} ListNode_t;

/**
 * struct CommandInfo - Represents information related to a command execution
 * @arg: The main argument for the command
 * @argv: Array of arguments for the command
 * @path: Path to the executable for the command
 * @argc: Number of arguments in the command
 * @line_count: Line number associated with the command
 * @err_num: Error code for exit() calls
 * @linecount_flag: Flag to indicate whether to count this line of input
 * @fname: The program filename
 * @environ: Custom modified copy of the environment variables
 * @env_changed: Flag indicating if the environment was changed
 * @status: The return status of the last executed command
 * @cmd_buf: Pointer to a chain buffer for storing commands (memory management)
 * @cmd_buf_type: Type of command in the buffer (CMD_type ||, &&, ;)
 * @readfd: File descriptor from which to read line input
 * @histcount: Count of the history line number
 * @env: Linked list representing the local copy of the environment (environ)
 * @alias: Linked list representing command aliases
 * @history: Linked list representing the history of executed commands
 */
typedef struct CommandInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
	ListNode_t *env;
	ListNode_t *alias;
	ListNode_t *history;
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
char **splitStr(char *s, char *d);
char **splitStr2(char *s, char *d);

/* ErrorStringFunctions */

void customPrintString(char *inputStr);
int customPrintCharToStderr(char character);
int writeToFD(char character, int fileDescriptor);
int printStringToFD(char *inputStr, int fileDescriptor);

/* MemoryFunctions */
char *_memset(char *s, char b, unsigned int n);
void *reallocMemory(void *ptr, unsigned int oldSize, unsigned int newSize);
void freeStringArray(char **stringArray);
int freeAndNullify(void **pointer);

/* shell_operations.c */
int runShell(CommandInfo_t *, char **);
int findBuiltInCommand(CommandInfo_t *);
void findCommandInPath(CommandInfo_t *);
void executeCommand(CommandInfo_t *);

/* path_operations.c */
int isCommandInPath(CommandInfo_t *, char *);
char *duplicateSubstring(char *, int, int);
char *findExecutablePath(CommandInfo_t *, char *, char *);

#endif /* MAIN_H */
