/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:38:59 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 22:27:30 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_nothing(char **arr, t_minishell *minish);

int	cmd_run(char **arr, t_minishell *minish, int cmd_type)
{
	if (cmd_type == C_EMPTY || cmd_type == C_BLANK)
		run_nothing(arr, minish);
	else if (cmd_type == C_ECHO)
	{
		run_echo(arr + 1, 0, 0, 0);
		minish->exit_status = SUCCESS;
	}
	else
	{
		minish->exit_status = SUCCESS;
		if (cmd_type == C_CD)
			run_cd(arr + 1, minish, 0);
		else if (cmd_type == C_PWD)
			run_pwd(arr + 1, minish);
		else if (cmd_type == C_EXPORT)
			run_export(arr + 1, minish);
		else if (cmd_type == C_UNSET)
			run_unset(arr + 1, minish);
		else if (cmd_type == C_ENV)
			run_env(arr + 1, minish);
		else if (cmd_type == C_EXIT)
			run_exit(arr + 1, minish, 0);
	}
	return (minish->exit_status);
}

static void	run_nothing(char **arr, t_minishell *minish)
{
	if (*arr == 0)
		return ;
	minish->exit_status = CMD_NF_FAILURE;
	print_err_msg(*arr, ": Command not found\n");
}
