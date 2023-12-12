#include "main.h"

/**
 * clear_info - Initializes the Commandinfo_t structure.
 * @info: Address of the structure.
 */
void clear_info(Commandinfo_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
	info->line_count = 0;
	info->err_num = 0;
	info->linecount_flag = 0;
	info->fname = NULL;
	info->environ = NULL;
	info->env_changed = 0;
	info->status = 0;
	info->cmd_buf = NULL;
	info->cmd_buf_type = 0;
	info->readfd = 0;
	info->histcount = 0;
	info->env = NULL;
	info->alias = NULL;
	info->history = NULL;
}

/**
 * set_info - Initializes the Commandinfo_t structure with argument vector.
 * @info: Address of the structure
 * @av: Argument vector
 */
void set_info(Commandinfo_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
			else
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Releases the fields of the info_t structure
 * @info: Address of the structure
 * @all: True if freeing all fields
 */
void free_info(Commandinfo_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&info->env);
		if (info->history)
			free_list(&info->history);
		if (info->alias)
			free_list(&info->alias);

		ffree(info->environ);
		info->environ = NULL;

		bfree((void **)&info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(-1);
	}
}
