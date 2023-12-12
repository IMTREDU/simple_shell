#include "main.h"

/**
 * main - Main function for the shell.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	Commandinfo_t info[] = { EMPTY_COMMAND_INFO };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			handle_open_error(av);
			return EXIT_FAILURE;
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

/**
 * handle_open_error - Handle errors during file opening.
 * @av: Argument vector.
 */
void handle_open_error(char **av)
{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
		_eputs(av[0]);
		_eputs(": 0: Can't open ");
		_eputs(av[1]);
		_eputchar('\n');
		_eputchar(-1);
		exit(127);
	}
}
