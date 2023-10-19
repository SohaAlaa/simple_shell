#include "shell.h"

/**
 * exe.cmd - is a fn that determines if a file is an executable command
 *   the info struct
 *-paath: paath to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int exe.cmd(info.t *info, char *paath)
{
	struct stat st;

	(void)info;
	if (!paath || stat(paath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dplechar - is a fn that duplicates characters
 *-paathstr: the paath string
 *-start: starting index
 *-stop: stopping index
 *
 * Return: pointer to new bufffer
 */
char *dplechar(char *paathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (paathstr[i] != ':')
			buff[k++] = paathstr[i];
	buff[k] = 0;
	return (buff);
}

/**
 * fd.paath -is a fn that  finds this cmd in the paath string
 *   the info struct
 *-paathstr: the paath string
 *-cmd: the cmd to find
 *
 * Return: full paath of cmd if found or NULL
 */
char *fd.paath(info.t *info, char *paathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *paath;

	if (!paathstr)
		return (NULL);
	if ((stringto_length(cmd) > 2) && check_starts(cmd, "./"))
	{
		if (exe.cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!paathstr[i] || paathstr[i] == ':')
		{
			paath = dplechar(paathstr, curr_pos, i);
			if (!*paath)
				str.concatenates(paath, cmd);
			else
			{
				str.concatenates(paath, "/");
				str.concatenates(paath, cmd);
			}
			if (exe.cmd(info, paath))
				return (paath);
			if (!paathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
