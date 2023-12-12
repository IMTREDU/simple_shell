#include "main.h"

/**
 * is_cmd - Checks if a file is an executable command
 * @info: The information struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(Commandinfo_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
 * dup_chars - Creates a duplicate of characters.
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (i = start; i < stop && pathstr[i] != ':'; i++)
		buf[k++] = pathstr[i];

	buf[k] = '\0';
	return (buf);
}

/**
 * find_path - Locates the specified command in the PATH string
 * @info: The information struct
 * @pathstr: the PATH string
 * @cmd: The command to find
 *
 * Return: Full path of the command if found
 */
char *find_path(Commandinfo_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			_strcat(path, (path[0] ? "/" : ""));
			_strcat(path, cmd);
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
