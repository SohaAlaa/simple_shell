#include "shell.h"

/**
 * ip_bufff -is a fn that bufffers chained commands
 *   parameter struct
 *-buff: address of bufffer
 *-len: address of len var
 *
 * Return: bytes read
 */
ssize_t ip_bufff(info.t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the bufffer, fill it */
	{
		/*b_free((void **)info->cmd_buff);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_getoneline
		r = getline(buff, &len_p, stdin);
#else
		r = _getoneline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->no.line__flag = 1;
			rmvcomment(*buff);
			buildhistory_list(info, *buff, info->histcount++);
			/* if (locate-char(*buff, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * get_ip - is a fn that gets a line minus the newline
 *   parameter struct
 *
 * Return: bytes read
 */
ssize_t get_ip(info.t *info)
{
	static char *buff; /* the ';' command chain bufffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(buff_FLUSH);
	r = ip_bufff(info, &buff, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* if we have commands left in the chain bufffer */
	{
		j = i; /* if init new iterator to current buff position */
		p = buff + i; /* get pointer for return */

		check.c(info, buff, &j, i, len);
		while (j < len) /* it iterate to semicolon or end */
		{
			if (is.ch(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* it increment past nulled ';'' */
		if (i >= len) /* reached end of bufffer? */
		{
			i = len = 0; /* reset position and lengths */
			info->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p; /* it pass back pointer to current command position */
		return (stringto_length(p)); /* return lengths of current command */
	}

	*buff_p = buff; /* if else not a chain, pass back bufffer from _getoneline() */
	return (r); /* return lengths of bufffer from _getoneline() */
}

/**
 * readbuff - if it is a fn that reads a bufffer
 *   parameter struct
 *-buff: bufffer
 *-i: size
 *
 * Return: r
 */
ssize_t readbuff(info.t *info, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, readbuff_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getoneline -  is a fn that gets the next line of input from STDIN
 *   parameter struct
 *-ptr: address of pointer to bufffer, preallocated or NULL
 *-lengths: size of preallocated ptr bufffer if not NULL
 *
 * Return: s
 */
int _getoneline(info.t *info, char **ptr, size_t *lengths)
{
	static char buff[readbuff_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && lengths)
		s = *lengths;
	if (i == len)
		i = len = 0;

	r = readbuff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = locate-char(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lengths)
		*lengths = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_Handler - is a fn that blocks ctrl-C
 * sig_num: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(buff_FLUSH);
}
