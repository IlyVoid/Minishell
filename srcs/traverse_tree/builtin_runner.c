/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_runner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:40:49 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 18:34:58 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int		run_without_redir(char **cmd, t_minishell *minish, int cmd_type);
int		run_with_redir(char **cmd, char **redir, t_minishell *minish,
			int cmd_type);
int		cpy_fd_std(int *in_fd, int *out_fd, char *cmd);
void	return_fd_std(int *in_fd, int *out_fd, int *status, char *cmd);

int	builtin_runner(char **cmd, char **redir, t_minishell *minish, int cmd_type)
{
	int	status;

	if (!redir)
		status = run_without_redir(cmd, minish, cmd_type);
	else
		status = run_with_redir(cmd, redir, minish, cmd_type);
	return (status);
}

int	run_without_redir(char **cmd, t_minishell *minish, int cmd_type)
{
	int	status;

	status = cmd_run(cmd, minish, cmd_type);
	return (status);
}

int	run_with_redir(char **cmd, char **redir, t_minishell *minish, int cmd_type)
{
	int	status;
	int	in_fd;
	int	out_fd;

	status = cpy_fd_std(&in_fd, &out_fd, cmd[0]);
	if (status == 0)
		status = apply_redirects(redir, minish);
	if (status == 0)
		status = cmd_run(cmd, minish, cmd_type);
	return_fd_std(&in_fd, &out_fd, &status, cmd[0]);
	return (status);
}

int	cpy_fd_std(int *in_fd, int *out_fd, char *cmd)
{
	*in_fd = dup(STDIN_FILENO);
	*out_fd = dup(STDOUT_FILENO);
	if (*in_fd == -1 || *out_fd == -1)
	{
		if (*in_fd != -1)
			close(*in_fd);
		if (*out_fd != -1)
			close(*out_fd);
		print_err_msg(cmd, ": occurence of dup() error");
		return (DUP_FAILURE);
	}
	return (0);
}

void	return_fd_std(int *in_fd, int *out_fd, int *status, char *cmd)
{
	int	redir_status;

	redir_status = 0;
	if (dup2(*in_fd, STDIN_FILENO) == -1 || dup2(*out_fd, STDOUT_FILENO) == -1)
	{
		print_err_msg(cmd, ": occurence of dup2() error"
			"possible error in behaviour\n");
		redir_status = DUP_FAILURE;
	}
	close(*in_fd);
	close(*out_fd);
	if (*status == 0)
		*status = redir_status;
}
