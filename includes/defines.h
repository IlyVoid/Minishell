/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:56:09 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 15:56:13 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

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
	CD_LENGTH,
	PWD_LENGTH,
	ECHO_LENGTH,
	ENV_LENGTH,
	EXIT_LENGTH,
	UNSET_LENGTH,
	EXPORT_LENGTH,
};

enum	e_signals
{
	HEREDOC,
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

#endif
