#include "../../includes/minishell.h"

static void remove_space_and_quotes_hd(char *hd);
static void heredoc(char *limiter, int fd, t_minishell *minish);
static void handle_line_heredoc(int fd, char *line, t_minishell *minish, char *limiter);

int prepare_heredoc(char **limiter, char *hd_name, t_minishell *minish)
{
	int     status;
	pid_t   pid;
	innt    fd;

	remove_space_and_quotes_hd(*limiter + 2);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		signal_interceptor(HEREDOC);
		toggler(IMPLICIT);
		fd = open(hd_name + 2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd != -1)
			heredoc(*limiter + 2, fd, minish);
		exit(GENERIC_ERROR);
	}
	free(*limiter);
	*limiter = hd_name;
	status = wait_childrem(&pid, 1);
	return (status);
}

void    remove_spaces_and_quotes_hd(char *hd)
{
	int i;

	while (ft_isspace(*hd))
	{
		i = 0;
		while (hd[i] != NULL_TERM)
		{
			hd[i] = hd[i + 1];
			i++;
		}
	}
	remove_quotes(hd, 0, 0);
}

static void heredoc(char *limiter, int fd, t_minishell *minish)
{
	char    *line;
	int     isequal;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			ft_printf("\033[1A");
			ft_printf("\033[2C");
			exit(0);
		}
		isequal = ft_strcmp(limiter, line);
		if (isequal != 0)
			handle_line_heredoc(fd, line, minish, limiter);
		if (isequal == 0)
		{
			close(fd);
			exit(0);
		}
	}
}