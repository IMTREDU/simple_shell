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
} Commandinfo_t;

#define EMPTY_COMMAND_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, 0, 0, NULL, 0, 0, 0, \
	NULL, NULL, NULL}

/**
 * struct BuiltinCommand - Represents a built-in command with its related function
 * @type: The built-in command string identifier
 * @func: Pointer to the associated function for the built-in command
 */
typedef struct BuiltinCommand
{
	char *type;
	int (*func)(Commandinfo_t *);
} BuiltinCommandTable_t;

/* StringFunctions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *starts_with(const char *haystack, const char *needle);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/* ErrorStringFunctions */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* MemoryFunctions */
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ffree(char **pp);
int bfree(void **ptr);

/* path_operations.c */
int is_cmd(Commandinfo_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(Commandinfo_t *info, char *pathstr, char *cmd);

/* ShellCommand.c or hsh.c */
int hsh(Commandinfo_t *info, char **av);
int find_builtin(Commandinfo_t *info);
void find_cmd(Commandinfo_t *info);
void fork_cmd(Commandinfo_t *info);

/* interactive_operations.c and error_handling.c */
int interactive(Commandinfo_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char * s);
int _erratoi(char *s);
void print_error(Commandinfo_t *, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* builtin_operations.c */
int _myexit(Commandinfo_t *info);
int _mycd(Commandinfo_t *info);
int _myhelp(Commandinfo_t *info);
int _myhistory(Commandinfo_t *info);
int unset_alias(Commandinfo_t *info, char *str);
int set_alias(Commandinfo_t *info, char *str);
int print_alias(ListNode_t *node);
int _myalias(Commandinfo_t *info);

/* input_operations.c */
ssize_t input_buf(Commandinfo_t *info, char **buf, size_t *len);
ssize_t get_input(Commandinfo_t *info);
ssize_t read_buf(Commandinfo_t *info, char *buf, size_t *i);
int _getline(Commandinfo_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* info_operations.c */
void clear_info(Commandinfo_t *info);
void set_info(Commandinfo_t *info, char **av);
void free_info(Commandinfo_t *info, int all);

/* env_operations.c */
int _myenv(Commandinfo_t *info);
char *_getenv(Commandinfo_t *info, const char *name);
int _mysetenv(Commandinfo_t *info);
int _myunsetenv(Commandinfo_t *info);
int populate_env_list(Commandinfo_t *info);
char **get_environ(Commandinfo_t *info);
int _unsetenv(Commandinfo_t *info, char *var);
int _setenv(Commandinfo_t *info, char *var, char *value);

/* history_operations.c */
char *get_history_file(Commandinfo_t *info);
int write_history(Commandinfo_t *info);
int read_history(Commandinfo_t *info);
int build_history_list(Commandinfo_t *info, char *buf, int linecount);
int renumber_history(Commandinfo_t *info);

/* list_operations.c */
ListNode_t *add_node(ListNode_t **head, const char *str, int num);
ListNode_t *add_node_end(ListNode_t **head, const char *str, int num);
size_t print_list_str(const ListNode_t *h);
int delete_node_at_index(ListNode_t **head, unsigned int index);
void free_list(ListNode_t **head_ptr);
size_t list_len(const ListNode_t *h);
char **list_to_strings(ListNode_t *head);
size_t print_list(const ListNode_t *h);
ListNode_t *node_starts_with(ListNode_t *node, char *prefix, char c);
ssize_t get_node_index(ListNode_t *head, ListNode_t *node);

/* command_processing.c */
int is_chain(Commandinfo_t *info, char *buf, size_t *p);
void check_chain(Commandinfo_t *info, char *buf, size_t *p, size_t i, size_t l);
int replace_alias(Commandinfo_t *info);
int replace_vars(Commandinfo_t *info);
int replace_string(char **old, char *new);

/* Main.c */
void handle_open_error(char **av);

#endif /* MAIN_H */
