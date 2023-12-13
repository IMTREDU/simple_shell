#include "main.h"

/**
 * get_environ - Provides a copy of the string array
 * @info: Structure with potential arguments
 *
 * Return: Always returns 0
 */
char **get_environ(Commandinfo_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes a specified environment variable
 * @info: Structure containing potential arguments
 *
 * @var: The string property of the environment variable.
 * Return: 1 on successful deletion, 0 otherwise.
 */
int _unsetenv(Commandinfo_t *info, char *var)
{
	ListNode_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);
	while (node)
	{
		if (starts_with(node->str, var) && node->str[strlen(var)] == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
		}
		else
		{
			node = node->next;
			i++;
		}
	}
	return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment var or modifies an existing one
 *
 * @info: Structure containing potential arguments
 *
 * @var: The string property of the environment variable.
 * @value: The string value of the environment variable.
 *  Return: Always returns 0.
 */
int _setenv(Commandinfo_t *info, char *var, char *value)
{
	ListNode_t *node;
	char *buf, *p;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	for (node = info->env; node; node = node->next)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (free(buf), 0);
		}
	}
	add_node_end(&(info->env), buf, 0);
	info->env_changed = 1;
	return (0);
}
