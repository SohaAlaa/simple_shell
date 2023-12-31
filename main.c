#include "shell.h"

/**
 * main - is a fn that entry point
 * ac: arg count
 * av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
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
				_prt_ip_str(av[0]);
				_prt_ip_str(": 0: Can't open ");
				_prt_ip_str(av[1]);
				_wr_char_c('\n');
				_wr_char_c(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_env_LL(info);
	rd_from_file(info);
	mainShellLoop(info, av);
	return (EXIT_SUCCESS);
}
