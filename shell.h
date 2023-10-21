#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define rd_from_buffer_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for cloneCvrt() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USEget_next_line_from_std 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - is a fn that singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *contain_pseudo - is a fn that contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *arg: a string generated from getline containing arguements
 *argv: an array of strings generated from arg
 *path: a string path for the current command
 *argc: the argument count
 *line_count: the error count
 *num_error: the error code for exit()s
 *linecount_flag: if on count this line of input
 *fname: the program filename
 *env: linked list local copy of environ
 *environ: custom modified copy of environ from LL env
 *history: the history node
 *alias: the alias node
 *env_changed: on if environ was changed
 *status: the return status of the last exec'd command
 *cmd_buf: address of pointer to cmd_buf, on if chaining
 *cmd_buf_type: CMD_type ||, &&, ;
 *readfd: the fd from which to read line input
 *histcount: the history line number count
 */
typedef contain_pseudo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int num_error;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *built-in_ruction - is a fn that contains a builtin string and related function
 *type: the builtin command flag
 *func: the function
 */
typedef built-in_ruction
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* h_s.c */
int mainShellLoop(info_t *, char **);
int find_comm_in(info_t *);
void find_comm_inPath(info_t *);
void fk_exec_thread(info_t *);

/* track.c */
int _exec(info_t *, char *);
char *repeatChar(char *, int, int);
char *cmd_pathStr(info_t *, char *, char *);

/* loophsh.C */
int loophsh(char **);

/* errorstr_fns.c */
void _prt_ip_str(char *);
int _wr_char_c(char);
int _wr_char_c_fd(char c, int fd);
int _prt_ip_strfd(char *str, int fd);

/* setof_str_fns.c */
int _return_length(char *);
int _compare_lexo(char *, char *);
char *_check_haystack(const char *, const char *);
char *_strcat(char *, char *);

/* setof_str_fns2.c */
char * copy_strings(char *, char *);
char *double_the_string(const char *);
void prt_ip_string(char *);
int wr_charC_out(char);

/* setof_str_fns3.c */
char *copy_theSTR(char *, char *, int);
char * concat_strings(char *, char *, int);
char * add_character_toSTR(char *, char);

/* setof_str_fns4.c */
char **split_in_words(char *, char *);
char **split_in_words2(char *, char);

/* memory_functions */
char *fill_wt_const(char *, char, unsigned int);
void letgo_strof_strs(char **);
void *_arrange(void *, unsigned int, unsigned int);

/* fns_in_Memory2.c */
int letgo_pointer_and_address(void **);

/* Extrafns.c */
int _true_shell_intact_mode(info_t *);
int_char_is_deli(char, char *);
int  fn_checks_alphabchar(int);
int conv_a_str_to_int(char *);

/* Extrafns2.c */
int _conv_str_int(char *);
void msg_wrong(info_t *, char *);
int prt_decimal(int, int);
char *cloneCvrt(long int, int, int);
void no_cmm(char *);

/* built_in_em.c */
int _exitshell(info_t *);
int _cd(info_t *);
int change_current_dir(info_t *);

/* built_inem2.c */
int display_H_list(info_t *);
int symbol_alias(info_t *);

/* enterline.c module */
ssize_t line_minus_new(info_t *);
int get_next_line_from_std(info_t *, char **, size_t *);
void blockCtrl_c(int);

/* whole_informations.c module */
void int_info_struct(info_t *);
void init_infoT_struct(info_t *, char **);
void field_info_to_be_free(info_t *, int);

/* ev.c module */
char *get_valu_envir(info_t *, const char *);
int prt_current_environ(info_t *);
intinit_new_envir_var(info_t *);
int rm_envir_var(info_t *);
int pop_env_LL(info_t *);

/* ev2.c module */
char **return_str_array(info_t *);
int rm_env_var(info_t *, char *);
int _init_new_env_var(info_t *, char *, char *);

/* fileio_fns.c */
char *list_hist(info_t *info);
int cr_pnd_to_file(info_t *info);
int rd_from_file(info_t *info);
int add_to_LL(info_t *info, char *buf, int linecount);
int change_LL_no(info_t *info);

/* string_in_list.c module */
list_t *start_a_L(list_t **, const char *, int);
list_t *start_a_L_end(list_t **, const char *, int);
size_t prt_only_string_LL(const list_t *);
int delnode_of_no(list_t **, unsigned int);
void letgo_all_nodes(list_t **);

/* string_in_list2.c module */
size_t length_of_LL(const list_t *);
char **arr_strs_of_L(list_t *);
size_t prt_ele_L(const list_t *);
list_t *begin_from_prefix(list_t *, char *, char);
ssize_t return_by_no(list_t *, list_t *);

/* chin.c */
int test_char_delimeter(info_t *, char *, size_t *);
void cont_ch_Ch(info_t *, char *, size_t *, size_t, size_t);
int rp_alias_to_token(info_t *);
int rp_vairble_to_tokenstr(info_t *);
int str_rp(char **, char *);

#endif

