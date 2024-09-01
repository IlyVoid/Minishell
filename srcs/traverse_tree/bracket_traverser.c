/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_traverser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:32:56 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/31 19:37:23 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bracket_traverser(t_node **root, t_minishell *minish)
{
	int		status;
	pid_t	pid;
	t_node	*node;

	if (minish->is_parent == false)
		signal_interceptor(DEFAULT); // yet to create
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHOLD)
	{
		signal_interceptor(DEFAULT);
		minish->is_parent = false;
		node = *root;
		status = tree_traverser(&(node->left), minish); // in progress
		exit (status);
	}
	else
		status = wait_childs(&pid, 1);
	return (status);
}
