#include "shell.h"

/**
 * _exitshell - is a fn that exits the shell
 * Struct containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exitshell(info_t *info)
{
	int checkexit;

	if (info->argv[1])  /* If there is an exit argument */
	{
		checkexit = _conv_str_int(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			msg_wrong(info, "Illegal number: ");
			_prt_ip_str(info->argv[1]);
			_wr_char_c('\n');
			return (1);
		}
		info->num_error = _conv_str_int(info->argv[1]);
		return (-2);
	}
	info->num_error = -1;
	return (-2);
}

/**
 * _cd - is a fn that  changes the current directory of the process
 * Struct containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int changedir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		prt_ip_string("TODO: >>getcwd failure msg<<\n");
	if (!info->argv[1])
	{
		dir = get_valu_envir(info, "HOME=");
		if (!dir)
			changedir_ret = /* TODO: what should this be? */
				chdir((dir = get_valu_envir(info, "PWD=")) ? dir : "/");
		else
			changedir_ret = chdir(dir);
	}
	else if (_compare_lexo(info->argv[1], "-") == 0)
	{
		if (!get_valu_envir(info, "OLDPWD="))
		{
			prt_ip_string(s);
			wr_charC_out('\n');
			return (1);
		}
		prt_ip_string(get_valu_envir(info, "OLDPWD=")), wr_charC_out('\n');
		changedir_ret = /* TODO: what should this be? */
			chdir((dir = get_valu_envir(info, "OLDPWD=")) ? dir : "/");
	}
	else
		changedir_ret = chdir(info->argv[1]);
	if (changedir_ret == -1)
	{
		msg_wrong(info, "can't cd to ");
		_prt_ip_str(info->argv[1]), _wr_char_c('\n');
	}
	else
	{
		_init_new_env_var(info, "OLDPWD", get_valu_envir(info, "PWD="));
		_init_new_env_var(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * change_current_dir -is a fn that  changes the current directory of the process
 * Struct containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_current_dir(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	prt_ip_string("help call works. Function not yet implemented \n");
	if (0)
		prt_ip_string(*arg_array); /* temp att_unused workaround */
	return (0);
}
