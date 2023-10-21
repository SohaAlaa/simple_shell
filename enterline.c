#include "shell.h"

/**
 * bufferchain_command - is a fn that buffers chained commands
 * info: parameter struct
 * buf: address of buffer
 * len: address of len var
 *
 * Return: bytes read
 */
ssize_t bufferchain_command(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*letgo_pointer_and_address((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, blockCtrl_c);
#if USEget_next_line_from_std
		r = getline(buf, &len_p, stdin);
#else
		r = get_next_line_from_std(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			no_cmm(*buf);
			add_to_LL(info, *buf, info->histcount++);
			/* if ( add_character_toSTR(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * line_minus_new - is a fn that gets a line minus the newline
 * info: parameter struct
 *
 * Return: bytes read
 */
ssize_t line_minus_new(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	wr_charC_out(BUF_FLUSH);
	r = bufferchain_command(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		cont_ch_Ch(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (test_char_delimeter(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_return_length(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_next_line_from_std() */
	return (r); /* return length of buffer from get_next_line_from_std() */
}

/**
 * rd_from_buffer - is a fn that reads a buffer
 * info: parameter struct
 * buf: buffer
 * i: size
 *
 * Return: r
 */
ssize_t rd_from_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, rd_from_buffer_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_next_line_from_std - is a fn that gets the next line of input from STDIN
 * info: parameter struct
 * ptr: address of pointer to buffer, preallocated or NULL
 * length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_next_line_from_std(info_t *info, char **ptr, size_t *length)
{
	static char buf[rd_from_buffer_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = rd_from_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c =  add_character_toSTR(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _arrange(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		 concat_strings(new_p, buf + i, k - i);
	else
		copy_theSTR(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * blockCtrl_c - is a fn that blocks ctrl-C
 * sig_num: the signal number
 *
 * Return: void
 */
void blockCtrl_c(__attribute__((unused))int sig_num)
{
	prt_ip_string("\n");
	prt_ip_string("$ ");
	wr_charC_out(BUF_FLUSH);
}
