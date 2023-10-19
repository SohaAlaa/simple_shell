#include "shell.h"

/**
 * main -is a fn that is entry point
 *-ac: arg count
 *-av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info.t info[] = { INFO_INIT };
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
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs(av[0]);
				eputs(": 0: Can't open ");
				eputs(av[1]);
				_eput.ch('\n');
				_eput.ch(buff_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_ev_list(info);
	readhistory(info);
	__hsh(info, av);
	return (EXIT_SUCCESS);
}
