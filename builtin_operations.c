#include "main.h"

/**
 * _myexit - Exits the shell with a specified exit status
 * @info: Structure with potential arguments
 *
 * Return: Exits the shell.
 *
 */
int _myexit(Commandinfo_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}


/**
 * _mycd - Changes the current directory of the process.
 * @info: Structure with potential arguments
 *
 *  Return: Always returns 0.
 */
int _mycd(Commandinfo_t *info)
{
	char *dir, buffer[1024];
	int chdir_ret;

	if (!(getcwd(buffer, 1024)))
		_puts("Error: Unable to retrieve current working directory.\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=") ?
			_getenv(info, "HOME=") :
			_getenv(info, "PWD=");
		chdir_ret = chdir(dir ? dir : "/");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(getcwd(buffer, sizeof(buffer)));
			_putchar('\n');
			return (1);
		}
		_puts(dir);
		_putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Error: Unable to change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}

/**
 * _myhelp - Provides assistance or information about the shell.
 * @info: Structure with potential arguments
 *
 *  Return: Always returns 0
 */
int _myhelp(Commandinfo_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("The 'help' command is not yet implemented.\n");

	if (0)
		_puts(*arg_array);
	return (0);
}
