/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:37:42 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/26 15:54:49 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err_msg(char *cmd, char *msg)
{
	cmd = ft_strjoin("\033[0;31md-sh: \033[0;0m", cmd);
	if (!cmd)
		return ;
	msg = ft_strjoin(cmd, msg);
	free(cmd);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}


