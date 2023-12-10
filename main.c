#include "main.h"

/**
 * main - Entry point for the custom shell program
 * @argc: The number of arguments passed to the program
 * @argv: Array of pointers to the arguments
 * @env: Array of pointers to the environment variables
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int argc, char **argv, char **env)
{
	Commandinfo_t info;

	(void)argc;
	set_info(&info, argv);
	info.environ = env;
	interactive(&info);
	free_info(&info, 1);

	return (0);
}
