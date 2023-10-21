#include "shell.h"

/**
 * list_hist - is a fn that gets the history file
 * info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *list_hist(info_t *info)
{
	char *buf, *dir;

	dir = get_valu_envir(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_return_length(dir) + _return_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	 copy_strings(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * cr_pnd_to_file - is a fn that creates a file, or appends to an existing file
 * info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int cr_pnd_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = list_hist(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_prt_ip_strfd(node->str, fd);
		_wr_char_c_fd('\n', fd);
	}
	_wr_char_c_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_from_file - is a fn that reads history from file
 * info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_from_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = list_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_to_LL(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_to_LL(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delnode_of_no(&(info->history), 0);
	change_LL_no(info);
	return (info->histcount);
}

/**
 * add_to_LL - is a fn that adds entry to a history linked list
 * info: Structure containing potential arguments. Used to maintain
 * buf: buffer
 * linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int add_to_LL(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	end_L(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * change_LL_no - is a fn that renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int change_LL_no(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
