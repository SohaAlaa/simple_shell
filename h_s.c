#include "shell.h"

/**
 * mainShellLoop - is a fn that main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mainShellLoop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		int_info_struct(info);
		if (_true_shell_intact_mode(info))
			prt_ip_string("$ ");
		_wr_char_c(BUF_FLUSH);
		r = line_minus_new(info);
		if (r != -1)
		{
			init_infoT_struct(info, av);
			builtin_ret = find_comm_in(info);
			if (builtin_ret == -1)
				find_comm_inPath(info);
		}
		else if (_true_shell_intact_mode(info))
			wr_charC_out('\n');
		field_info_to_be_free(info, 0);
	}
	cr_pnd_to_file(info);
	field_info_to_be_free(info, 1);
	if (!_true_shell_intact_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->num_error == -1)
			exit(info->status);
		exit(info->num_error);
	}
	return (builtin_ret);
}

/**
 * find_comm_in - is a fn that finds a builtin command
 * info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_comm_in(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exitshell},
		{"env", prt_current_environ},
		{"help", change_current_dir},
		{"history", display_H_list},
		{"setenv",init_new_envir_var},
		{"unsetenv", rm_envir_var},
		{"cd", _cd},
		{"alias", symbol_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_compare_lexo(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_comm_inPath - is a fn that finds a command in PATH
 * info: the parameter & return info struct
 *
 * Return: void
 */
void find_comm_inPath(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = cmd_pathStr(info, get_valu_envir(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fk_exec_thread(info);
	}
	else
	{
		if ((_true_shell_intact_mode(info) || get_valu_envir(info, "PATH=")
			|| info->argv[0][0] == '/') && _exec(info, info->argv[0]))
			fk_exec_thread(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			msg_wrong(info, "not found\n");
		}
	}
}

/**
 * fk_exec_thread - is a fn that forks a an exec thread to run cmd
 * info: the parameter & return info struct
 *
 * Return: void
 */
void fk_exec_thread(info_t *info)
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
		if (execve(info->path, info->argv, return_str_array(info)) == -1)
		{
			field_info_to_be_free(info, 1);
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
				msg_wrong(info, "Permission denied\n");
		}
	}
}
