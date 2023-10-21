#include "shell.h"

/**
 * _exec - is a fn that determines if a file is an executable command
 * info: the info struct
 * path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _exec(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * repeatChar - is a fn that duplicates characters
 * pathstr: the PATH string
 * start: starting index
 * stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *repeatChar(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * cmd_pathStr - is a fn that finds this cmd in the PATH string
 * info: the info struct
 * pathstr: the PATH string
 * cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *cmd_pathStr(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_return_length(cmd) > 2) && _check_haystack(cmd, "./"))
	{
		if (_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = repeatChar(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_exec(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
