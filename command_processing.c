#include "main.h"

/**
 * is_chain - Checks if the current character in the buffer is chain delimiter
 * @info: The parameter structure
 * @buf: The character buffer
 * @p: Address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter else 0
 */
int is_chain(Commandinfo_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = 1;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = 2;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = 3;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks whether to continue chaining based on the last status.
 * @inf: The parameter structure
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @l: Length of buf
 *
 * Return: Void.
 */
void check_chain(Commandinfo_t *inf, char *buf, size_t *p, size_t i, size_t l)
{
	size_t j = *p;

	if (inf->cmd_buf_type == 2)
	{
		if (inf->status)
		{
			buf[i] = 0;
			j = l;
		}
	}
	if (inf->cmd_buf_type == 1)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			j = l;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replaces aliases in the tokenized string.
 * @info: The parameter structure.
 *
 * Return: 1 if true else 0
 */
int replace_alias(Commandinfo_t *info)
{
	int i;
	ListNode_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string
 * @info: The parameter structure
 *
 * Return: 1 if true else 0
 */
int replace_vars(Commandinfo_t *info)
{
	int i = 0;
	ListNode_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string
 * @old: Address of the old string
 * @new: The new string
 *
 * Return: 1 if true else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
