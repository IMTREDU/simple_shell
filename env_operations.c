#include "main.h"

/**
 * _myenv - Displays the current environment.
 * @info: Structure with potential arguments
 *
 * Return: Always returns 0.
 */
int _myenv(Commandinfo_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of a specified environment variable.
 * @info: Structure with potential arguments
 * @name: Name of the environment variable
 *
 * Return: The value of the environment variable
 */
char *_getenv(Commandinfo_t *info, const char *name)
{
	ListNode_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable
 *
 * @info: Structure with potential arguments
 *
 *  Return: Always returns 0.
 */
int _mysetenv(Commandinfo_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Number of arguements is incorrect\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes a specified environment variable
 * @info: Structure with potential arguments
 *
 *  Return: Always returns 0.
 */
int _myunsetenv(Commandinfo_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Fills the environment linked list.
 * @info: Structure with potential arguments
 *
 * Return: Always returns 0.
 */
int populate_env_list(Commandinfo_t *info)
{
	ListNode_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		if (add_node_end(&node, environ[i], 0) != 0)
			return (1);
	info->env = node;
	return (0);
}
