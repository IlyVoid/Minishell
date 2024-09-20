/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:38:59 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/20 15:49:41 by quvan-de         ###   ########.fr       */
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
		minish->exit_status = SUCCESS
	}
	else
}
