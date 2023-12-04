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
 *  @startIdx: starting index of the substring
 *  @endIdx: ending index of the substring
 *
 *  Return: pointer to the new buffer
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
 * findExecutablePath - finds the specified command in the PATH string
 * @cmdInfo: the command information struct
 * @pathStr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *findExecutablePath(CommandInfo_t *cmdInfo, char *pathStr, char *cmd)
{
	int i = 0, currPos = 0;
	char *path;

	if (!pathStr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (isCommandInPath(cmdInfo, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = duplicateSubstring(pathStr, currPos, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isCommandInPath(cmdInfo, path))
			{
				return (path);
			}
			if (!pathStr[i])
			{
				break;
			}
			currPos = i;
		}
		i++;
	}
	return (NULL);
}
