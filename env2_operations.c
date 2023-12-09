#include "main.h"

/**
 * copyEnv - Returns a copy of our environment as a string array.
 * @info: Structure with arguments, maintaining a constant prototype.
 * Return: Always 0
 */
char **copyEnv(Commandinfo_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnvVar2 - Removes an environment variable.
 * @info: Structure with arguments, maintaining a constant prototype.
 * @var: String representing the variable to be removed.
 * Return: 1 on success, 0 otherwise.
 */
int unsetEnvVar2(Commandinfo_t *info, char *var)
{
	ListNode_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * setEnvVar2 - Initializes or modifies an environment variable.
 * @info: Structure with arguments, maintaining a constant prototype.
 * @var: String representing the variable property.
 * @value: String representing the variable value.
 * Return: Always 0.
 */
int setEnvVar2(Commandinfo_t *info, char *var, char *value)
{
	char *buf = NULL;
	ListNode_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
