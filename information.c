#include "shell.h"

/**
 * the clr.informaton - is a fn that  initializes info.t struct
 *   struct address
 */
void clr.informaton(info.t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->paath = NULL;
	info->argc = 0;
}

/**
 * the set.information - is a fn that initializes info.t struct
 *   struct address
 *-av: argument vector
 */
void set.information(info.t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splittow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rp.alias(info);
		rp.vars(info);
	}
}

/**
 * freeinformation - is a fn that frees info.t struct fields
 *   struct address
 *-all: true if freeing all fields
 */
void freeinformation(info.t *info, int all)
{
	full.free(info->argv);
	info->argv = NULL;
	info->paath = NULL;
	if (all)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->ev)
			F.list(&(info->ev));
		if (info->history)
			F.list(&(info->history));
		if (info->alias)
			F.list(&(info->alias));
		full.free(info->eviron);
			info->eviron = NULL;
		b_free((void **)info->cmd_buff);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(buff_FLUSH);
	}
}
