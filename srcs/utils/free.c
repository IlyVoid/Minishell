/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:50:28 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/26 22:54:08 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(int **pipefd, int cnt)
{
	int	i;

	i = 0;
	if (!pipefd)
		return ;
	while (i < cnt)
	{
		if (pipefd[i])
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			free(pipefd[i]);
		}
		i++;
	}
	free(pipefd);
}

void	free_string(char *str)
{
	if (str)
		free(str);
}

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free (str[i]);
	free(str);
	str = NULL;
}

void	free_blocks(t_block *blocks)
{
	if (!blocks)
		return ;
	free_string(blocks->cmd_name);
	free_matrix(blocks->args);
	free(blocks);
}

void	free_exp(t_expand *exp)
{
	t_expand	*tmp;

	if (!exp)
		return ;
	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free(tmp->str);
		free(tmp);
	}
}
