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

/* is the fn that for rd/wr all the bufffers */
#define readbuff_SIZE 1024
#define WRITE_buff_SIZE 1024
#define buff_FLUSH -1

/* fn that for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* fn that for cvrt_no() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* fn that 1 if using system getline() */
#define USE_getoneline 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **eviron;


/**
 * struct liststr - fn that singly linked list
 *-num: the number field
 *-str: a string
 *-next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - fn that contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *-arg: a string generated from getline containing arguements
 *-argv: an array of strings generated from arg
 *-paath: a string paath for the current command
 *-argc: the argument count
 *-line_count: the error count
 *-err_num: the error code for exit()s
 *-no.line__flag: if on count this line of input
 *-fname: the program filename
 *-ev: linked list local copy of eviron
 *-eviron: custom modified copy of eviron from LL ev
 *-history: the history node
 *-alias: the alias node
 *-ev_changed: on if eviron was changed
 *-status: the return status of the last exec'd command
 *-cmd_buff: address of pointer to cmd_buff, on if chaining
 *-cmd_buff_type: CMD_type ||, &&, ;
 *-readfd: the fd from which to read line input
 *-histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *paath;
	int argc;
	unsigned int line_count;
	int err_num;
	int no.line__flag;
	char *fname;
	list_t *ev;
	list_t *history;
	list_t *alias;
	char **eviron;
	int ev_changed;
	int status;

	char **cmd_buff; /* pointer to cmd ; chain bufffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info.t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *_builtin_struct - fn that contains a builtin string and related function
 *-type: the builtin command _flag
 *-func: the function
 */
typedef _builtin_struct
{
	char *type;
	int (*func)(info.t *);
} builtin_table;


/* fn that __hsh.c */
int __hsh(info.t *, char **);
int f.builtin(info.t *);
void f.cmd(info.t *);
void forkcmd(info.t *);

/* fn that pths.c */
int exe.cmd(info.t *, char *);
char *dplechar(char *, int, int);
char *fd.paath(info.t *, char *, char *);

/* fn that loop__hsh.c */
int loop__hsh(char **);

/* fn that err_strfunctions.c */
void eputs(char *);
int _eput.ch(char);
int _put.fd(char c, int fd);
int _puts.fd(char *str, int fd);

/* fn that str.functions.c */
int stringto_length(char *);
int strings_comparison(char *, char *);
char *check_starts(const char *, const char *);
char *str.concatenates(char *, char *);

/* fn that stri.functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* fn that  stri.functions3.c  */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *locate-char(char *, char);

/* fn that  stri.functions4.c  */
char **splittow(char *, char *);
char **splittow2(char *, char);

/* fn that memory_functions */
char *_memoryset(char *, char, unsigned int);
void full.free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* fn that  mem.functions2.c */
intptr_free(void **);

/* fn that add.functions.c */
int _interact(info.t *);
int ch_delim(char, char *);
int ch_alpha(int);
int fn.atoi(char *);

/* fn that add.functions2.c */
int stringto_intger(char *);
void printsthe.er(info.t *, char *);
int prt-decimal(int, int);
char *cvrt_no(long int, int, int);
void rmvcomment(char *);

/* fn that built.in_em.c */
int _myexit(info.t *);
int _my.cd(info.t *);
int _my.help(info.t *);

/* fn that built.in_em2.c */
int _mhistory(info.t *);
int _m.alias(info.t *);

/* fn that get-line.c module */
ssize_t get_ip(info.t *);
int _getoneline(info.t *, char **, size_t *);
void sigint_Handler(int);

/*fn that information.c module */
void clr.informaton(info.t *);
void set.information(info.t *, char **);
void freeinformation(info.t *, int);

/* fn that ev.c module */
char *_getev(info.t *, const char *);
int_myev(info.t *);
int_mysetev(info.t *);
int _myunsetev(info.t *);
int populate_ev_list(info.t *);

/* fn that ev2.c module */
char **get_eviron(info.t *);
int _unsetev(info.t *, char *);
int _setev(info.t *, char *, char *);

/* fn that file_io_fns.c */
char *get_history.file(info.t *info);
int writehistory(info.t *info);
int readhistory(info.t *info);
int buildhistory_list(info.t *info, char *buff, int linecount);
int renumber.history(info.t *info);

/* fn that list-string.c module */
list_t *add.a.node(list_t **, const char *, int);
list_t *add.a.node_end(list_t **, const char *, int);
size_t printliststring(const list_t *);
int del.a.nodeofindex(list_t **, unsigned int);
void F.list(list_t **);

/* fn that list-string2.c module */
size_t list_of_length(const list_t *);
char **strings_of_lists(list_t *);
size_t print.the.list(const list_t *);
list_t *node_check_starts(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* fn that ch.c */
int is.ch(info.t *, char *, size_t *);
void check.c(info.t *, char *, size_t *, size_t, size_t);
int rp.alias(info.t *);
int rp.vars(info.t *);
int rp.string(char **, char *);

#endif
