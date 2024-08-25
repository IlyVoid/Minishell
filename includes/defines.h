#ifndef DEFINES_H
# define DEFINES_H

enum    e_exit_status
{
	SUCCESS,
	GENERIC_ERROR,
	FORK_FAILURE = 400,
	PIPE_FAILURE = 500,
	DUP_FAILURE = 600,
};

enum    e_characters
{
	NULL_TERM,
};

# ifndef HEREDOC_NAME
#  define HEREDOC_NAME "<<.heredoc_"
# endif

#endif