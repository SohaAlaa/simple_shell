#include "shell.h"

/**
 * int_info_struct - initializes info_t struct
 * info: struct address
 */
void int_info_struct(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * init_infoT_struct - is a fn that initializes info_t struct
 * info: struct address
 * av: argument vector
 */
void init_infoT_struct(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_in_words(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = double_the_string(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rp_alias_to_token(info);
		rp_vairble_to_tokenstr(info);
	}
}

/**
 * field_info_to_be_free - is a fn that frees info_t struct fields
 * info: struct address
 * all: true if freeing all fields
 */
void field_info_to_be_free(info_t *info, int all)
{
	letgo_strof_strs(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			letgo_all_nodes(&(info->env));
		if (info->history)
			letgo_all_nodes(&(info->history));
		if (info->alias)
			letgo_all_nodes(&(info->alias));
		letgo_strof_strs(info->environ);
			info->environ = NULL;
		letgo_pointer_and_address((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		wr_charC_out(BUF_FLUSH);
	}
}
