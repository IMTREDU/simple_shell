#include "main.h"
#define HistoryFile ".simple_shell_history"

/**
 * get_history_file - Retrieves the path of the history file
 * @info: Parameter structure
 *
 * Return: Allocated string containing the history file path
 */

char *get_history_file(Commandinfo_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HistoryFile) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HistoryFile);
	return (buf);
}

/**
 * write_history - Creates a new file or appends to an existing history file.
 * @info: Parameter structure
 *
 * Return:  1 on success, -1 on failure
 */
int write_history(Commandinfo_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	ListNode_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(-1, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads the history from the file
 * @info: Parameter structure
 *
 * Return: The number of history entries on success, 0 on failure
 */
int read_history(Commandinfo_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= 4096)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Appends an entry to the history linked list
 * @info: Parameter structure with potential arguments
 * @buf: Buffer containing the history entry
 * @linecount: The current history line count
 *
 * Return: Always returns 0
 */
int build_history_list(Commandinfo_t *info, char *buf, int linecount)
{
	ListNode_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Updates the history count
 * @info: Parameter structure with potential arguments
 *
 * Return: The new history count
 */
int renumber_history(Commandinfo_t *info)
{
	ListNode_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
