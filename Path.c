#include "main.h"

/**
 * isCommandInPath - determines if a file is an executable command
 * @cmdInfo: the command information struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCommandInPath(CommandInfo_t *cmdInfo, char *path)
{
	struct stat st;

	(void)cmdInfo;
	if (!path || stat(path, &st))
	{
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateSubstring - duplicates characters in a substring
 * @inputStr: the input string
 * @startIdx: starting index of the substring
 * @endIdx: ending index of the substring
 *
 * Return: pointer to the new buffer
 */
char *duplicateSubstring(char *inputStr, int startIdx, int endIdx)
{
	static char buffer[1024];
	int bufferIdx = 0, inputIdx = 0;

	for (inputIdx = startIdx; inputIdx < endIdx; inputIdx++)
	{
		if (inputStr[inputIdx] != ':')
		{
			buffer[bufferIdx++] = inputStr[inputIdx];
		}
	}
	buffer[bufferIdx] = '\0';
	return (buffer);
}

/**
 * findExecutablePath - finds the specified command in path
 * @info: the command information struct
 * @pathStr: the string path
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *findExecutablePath(Commandinfo_t *info, char *pathstr, char *cmd)
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
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
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
