/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:56:09 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 20:44:11 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

enum	e_types
{
	T_AND,
	T_OR,
	T_BRACKET,
	T_PIPE,
	T_REDIR,
	T_CMD,
	T_CMD_BR,
};

enum	e_exit_status
{
	SUCCESS,
	GENERIC_ERROR,
	MALLOC_ERR = 200,
	FORK_FAILURE = 400,
	PIPE_FAILURE = 500,
	DUP_FAILURE = 600,
	CMD_PD_FAILURE = 126,
	CMD_ARG_ERROR,
	CMD_NF_FAILURE = 127,
	SYS_ERROR = 201,
	CHDIR_ERROR = 202,
	GETCWD_ERROR = 203,
	UNEXPECTED_EXIT = 255,
	SYNTAX_ERROR = 258,
	EXECVE_ERROR = 300,
};

enum	e_export_types
{
	EXPORT_ERROR = 1,
	EXPORT_EDIT,
	EXPORT_ADD,
	EXPORT_SKIP,
};

enum	e_wc_paths
{
	NO_PATH = 1,
	DOT_PATH,
	ABS_PATH,
};

enum	e_characters
{
	NULL_TERM,
	SEPERATOR = 31,
	PIPE = 124,
	D_QUOTE = 34,
	S_QUOTE = 39,
	SPCE = 32,
	HT = 9,
	NL = 10,
	AND = 38,
	DASH = 45,
	DOT = 46,
	SLASH = 47,
	O_ROUND = 40,
	C_ROUND = 41,
	REDIR_L = 60,
	REDIR_R = 62,
	COLON = 58,
	D_SIGN = 36,
	L_REDIR_SEP = 29,
	R_REDIR_SEP = 20,
	ASTERIX = 42,
	SEMICOLON = 59,
	EQUAL = 61,
	Q_MARK = 63,
	BACKSLASH = 92,
	UNDSCORE = 95,
	N_LOWER = 110,
};

enum	e_builtins
{
	NOT_BUILTIN,
	C_BLANK,
	C_EMPTY,
	C_ECHO,
	C_CD,
	C_ENV,
	C_EXPORT,
	C_PWD,
	C_UNSET,
	C_EXIT,
};

enum	e_builtins_length
{
	CD_LENGTH = 3,
	PWD_LENGTH = 4,
	ECHO_LENGTH = 5,
	ENV_LENGTH = 4,
	EXIT_LENGTH = 5,
	UNSET_LENGTH = 6,
	EXPORT_LENGTH = 7,
};

enum	e_signals
{
	HEREDOC,
	DEFAULT,
	INTERACTIVE,
	IGNORE,
};

enum	e_signals_echo
{
	IMPLICIT,
	EXPLICIT,
};

# ifndef HEREDOC_NAME
#  define HEREDOC_NAME "<<.heredoc_"
# endif

# ifndef CHILD
#  define CHILD 0
# endif

# ifndef FIRST
#  define FIRST 0
# endif

# ifndef SECOND
#  define SECOND 1
# endif

// history size
# ifndef HIST_SIZE
#  define HIST_SIZE 500
# endif

# ifndef WRITE
#  define WRITE 1
# endif

# ifndef READ
#  define READ 0
# endif

# ifndef NOT_FOUND
#  define NOT_FOUND -1
# endif

# ifndef NOT_EXPANDABLE
#  define NOT_EXPANDABLE -2
# endif

# ifndef PROMPT_STAT_LEN
#  define PROMPT_STAT_LEN 12
# endif

#endif
