/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:28:19 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 22:46:44 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	add_to_hst_lst(char *cmd, char *cmdline, t_minishell **minishell);
void	err_hst(char *cmd);

void	add_bash_hst(char *cmdline, t_minishell **minishell, int mode)
{
	t_minishell	*minish;
	char		*cmd;

	minish = *minishell;
	ft_remove_nl(cmdline);
	add_hst(cmdline);
	if (minish->history_path == NULL)
		return ;
	cmd = ft_strdup(cmdline);
	if (!cmd)
	{
		err_hst(cmdline);
		return ;
	}
	if (mode == 0)
		free(cmdline);
	add_to_hst_lst(cmd, cmdline, minishell);
}

void	add_to_hst_lst(char *cmd, char *cmdline, t_minishell **minishell)
{
	t_list		*curr;
	t_minishell	*minish;

	minish = *minishell;
	curr = ft_lstnew((void *)cmd);
	if (!curr)
	{
		free(cmd);
		err_hst(cmdline);
		return ;
	}
	ft_lstadd_back(&(minish->history), curr);
	if (ft_lstsize(minish->history) > HIST_SIZE)
		ft_lstdel_front(&(minish->history), free);
}

void	err_hst(char *cmd)
{
	ft_putstr_fd("\033[0;31md-sh: \033[0;0m", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": can't add to history, ", STDERR_FILENO);
}
