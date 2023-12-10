#include "main.h"

/**
 * input_buf - Buffers chained commands for processing
 * @info: Parameter structure containing relevant details
 * @buf: Address of the buffer to store the commands
 * @len: Address of the variable holding the length
 *
 * Return: Number of bytes read during processing
 */
ssize_t input_buf(Commandinfo_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);
		r = _getline(info, buf, &len_p);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Retrieves a line from the input
 * @info: Parameter structure with relevant information.
 *
 * Return: Number of bytes read during processing.
 */
ssize_t get_input(Commandinfo_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(-1);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads a buffer of specified size
 * @info: Parameter structure with necessary details
 * @buf: Buffer to read into
 * @i: Size of the buffer
 *
 * Return: The result of the buffer reading process.
 */
ssize_t read_buf(Commandinfo_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, 1024);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Reads the next line of input from the standard input
 * @info: Parameter structure with relevant information.
 * @ptr: Address of the pointer to the buffer
 * @length: Size of the preallocated ptr buffer
 *
 * Return: The result of reading the input line
 */
int _getline(Commandinfo_t *info, char **ptr, size_t *length)
{
	static char buf[1024];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Handles the Ctrl-C signal, preventing its default action.
 * @sig_num: The signal number associated with Ctrl-C.
 *
 * Return: Void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(-1);
}
