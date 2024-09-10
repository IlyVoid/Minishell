/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_traverser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:17:31 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/03 08:17:33 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	external_runner(char **cmnd, char **redir, t_minishell *minish);

int	cmd_traverser(char *cmd, char **redir, t_minishell *minish)
{
	int		cmd_type;
	int		status;
	char	**cmnd;

	status = parse_cmd(cmd, &cmnd, minish);
	if (status == 0)
	{
		cmd_type = is_builtin(cmnd[0]);
		if (cmd_type > 0)
			status = builtin_runner(cmnd, redir, minish, cmd_type);
		else
			status = external_runner(cmnd, redir, minish);
	}
	minish->exit_status = status;
	ft_free_2d_array(cmnd);
	return (status);
}

int	external_runner(char **cmnd, char **redir, t_minishell *minish)
{
	int		status;
	pid_t	pid;

	if (minish->is_parent == false)
		signal_interceptor(DEFAULT);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		status = 0;
		if (redir != NULL)
			status = apply_redirects(redir, minish);
		signal_interceptor(DEFAULT);
		toggler(EXPLICIT);
		if (status == 0)
			status = find_cmd(&cmnd[0], minish->env);
		if (status != 0)
			exit(status);
		execve(cmnd[0], cmnd, minish->env);
		print_err_msg(cmnd[0], ": occurence of execv() error\n");
		exit(EXECVE_ERROR);
	}
	status = wait_childs(&pid, 1);
	return (status);
}
