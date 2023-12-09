#include "main.h"

/**
 * bufferChainedCommands - Buffers chained commands for processing
 * @info: Parameter struct
 * @buf: Address of the buffer to store input
 * @len: Address of the variable to store the length
 *
 * Return: Number of bytes read.
 */
ssize_t bufferChainedCommands(Commandinfo_t *info, char **buf, size_t *len)
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
 * getInputLine - Retrieves a line from input
 * @info: Parameter struct
 *
 * Return: Number of bytes read
 */
ssize_t getInputLine(Commandinfo_t *info)
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
			info->cmd_buf_type = 0;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * readBuffer - Reads a buffer.
 * @info: Parameter struct
 * @buf: Buffer to read
 * @i: Size of the buffer
 *
 * Return: Result
 */
ssize_t readBuffer(Commandinfo_t *info, char *buf, size_t *i)
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
 * getNextLine - Gets the next line of input from STDIN.
 * @info: Parameter Struct
 * @ptr: Address of the pointer to the buffer , NULL
 * @length: Size of the preallocated buffer if not NULL.
 *
 * Return: Result
 */
int getNextLine(Commandinfo_t *info, char **ptr, size_t *length)
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
 * blockCtrlC - Blocks the interrupt signal (ctrl-C).
 * @sig_num: The signal number.
 *
 * Return: void
 */
void blockCtrlC(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(-1);
}
