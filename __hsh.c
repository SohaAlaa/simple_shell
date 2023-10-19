#include "shell.h"

/**
 * __hsh -  is a fn that is main shell loop
 *   the parameter & return info struct
 *-av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int __hsh(info.t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clr.informaton(info);
		if (_interact(info))
			_puts("$ ");
		_eput.ch(buff_FLUSH);
		r = get_ip(info);
		if (r != -1)
		{
			set.information(info, av);
			builtin_ret = f.builtin(info);
			if (builtin_ret == -1)
				f.cmd(info);
		}
		else if (_interact(info))
			_putchar('\n');
		freeinformation(info, 0);
	}
	writehistory(info);
	freeinformation(info, 1);
	if (!_interact(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * f.builtin - is a fn that finds a builtin command
 *   the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int f.builtin(info.t *info)
{
	int i, builtin.ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"ev",_myev},
		{"help", _my.help},
		{"history", _mhistory},
		{"setev",_mysetev},
		{"unsetev", _myunsetev},
		{"cd", _mycd},
		{"alias", _m.alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (strings_comparison(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin.ret = builtintbl[i].func(info);
			break;
		}
	return (builtin.ret);
}

/**
 * f.cmd -  is a fn that is a fn that finds a command in paath
 *   the parameter & return info struct
 *
 * Return: void
 */
void f.cmd(info.t *info)
{
	char *paath = NULL;
	int i, k;

	info->paath = info->argv[0];
	if (info->no.line__flag == 1)
	{
		info->line_count++;
		info->no.line__flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!ch_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	paath = fd.paath(info, _getev(info, "paath="), info->argv[0]);
	if (paath)
	{
		info->paath = paath;
		forkcmd(info);
	}
	else
	{
		if ((_interact(info) || _getev(info, "paath=")
			|| info->argv[0][0] == '/') && exe.cmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printsthe.er(info, "not found\n");
		}
	}
}

/**
 * forkcmd - is a fn that forks a an exec thread to run cmd
 *   the parameter & return info struct
 *
 * Return: void
 */
void forkcmd(info.t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->paath, info->argv, get_eviron(info)) == -1)
		{
			freeinformation(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printsthe.er(info, "Permission denied\n");
		}
	}
}
