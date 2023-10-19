#include "shell.h"

/**
 * get_history.file - is a fn that  gets the history file
 *   parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history.file(info.t *info)
{
	char *buff, *dir;

	dir = _getev(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (stringto_length(dir) + stringto_length(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	str.concatenates(buff, "/");
	str.concatenates(buff, HIST_FILE);
	return (buff);
}

/**
 * writehistory - is a fn that creates a file, or appends to an existing file
 *   the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writehistory(info.t *info)
{
	ssize_t fd;
	char *filename = get_history.file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts.fd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(buff_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readhistory - is a fn that reads history from file
 *   the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readhistory(info.t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history.file(info);

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
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			buildhistory_list(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildhistory_list(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		del.a.nodeofindex(&(info->history), 0);
	renumber.history(info);
	return (info->histcount);
}

/**
 * buildhistory_list -is a fn that adds entry to a history linked list
 *   Structure containing potential arguments. Used to maintain
 *-buff: bufffer
 *-linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildhistory_list(info.t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add.a.node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber.history - is a fn that renumbers the history linked list after changes
 *   Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber.history(info.t *info)
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
