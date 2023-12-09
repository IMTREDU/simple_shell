#include "main.h"

/**
 * printCurrentEnv - Outputs the current environment
 * @info: Structure with arguments, maintaining a constant prototype
 * Return: Always 0
 */
int printCurrentEnv(Commandinfo_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getEnvVar - Retrieves the value of a specified environment variable.
 * @info: Structure with arguments, maintaining a constant prototype.
 * @name: Name of the environment variable.
 *
 * Return: The value of the specified variable.
 */
char *getEnvVar(Commandinfo_t *info, const char *name)
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
 * setEnvVar - Initializes or modifies an environment variable
 * @info: Structure with arguments, maintaining a constant prototype
 * Return: Always 0
 */
int setEnvVar(Commandinfo_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvVar - Removes a specified environment variable.
 * @info: Structure with arguments, maintaining a constant prototype.
 * Return: Always 0
 */
int unsetEnvVar(Commandinfo_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvList - Fills the environment linked list with data.
 * @info: Structure with arguments, maintaining a constant prototype.
 * Return: Always 0
 */
int populateEnvList(Commandinfo_t *info)
{
	ListNode_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
