#include "shell.h"

/**
 * _m.exit - is a fn that exits the shell
 *   the Structure is containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _m.exit(info.t *info)
{
	int  exit.check;

	if (info->argv[1])  /* If there was an exit argument */
	{
		 exit.check = stringto_intger(info->argv[1]);
		if ( exit.check == -1)
		{
			info->status = 2;
			printsthe.er(info, "Illegal number: ");
			eputs(info->argv[1]);
			_eput.ch('\n');
			return (1);
		}
		info->err_num = stringto_intger(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _my.cd - is a fn that changes the current directory of the process
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my.cd(info.t *info)
{
	char *s, *dir, bufffer[1024];
	int chdir_ret;

	s = getcwd(bufffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getev(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getev(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strings_comparison(info->argv[1], "-") == 0)
	{
		if (!_getev(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getev(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getev(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printsthe.er(info, "can't cd to ");
		eputs(info->argv[1]), _eput.ch('\n');
	}
	else
	{
		_setev(info, "OLDPWD", _getev(info, "PWD="));
		_setev(info, "PWD", getcwd(bufffer, 1024));
	}
	return (0);
}

/**
 * _my.help -  is a fn that changes the current directory of the process
 *   Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my.help(info.t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
