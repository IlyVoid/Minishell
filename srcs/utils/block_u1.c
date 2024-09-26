/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_u1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:29:16 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/26 21:55:59 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir_error(t_block *block, char *str, char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (filename)
		free(filename);
	if (!block)
		return ;
	if (block->cmd_name)
		free_string(block->cmd_name);
	if (block->args)
		free_matrix(block->args);
	free(block);
}
