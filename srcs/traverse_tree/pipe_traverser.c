/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_traverser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:07 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 16:45:26 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	first_traversal(t_node **node, t_minishell *minish, int pipefd[2],
		int pids[2]);
int	second_traversal(t_node **node, t_minishell *minish, int pipefd[2],
		int pids[2]);

int	pipe_traverser(t_node **root, t_minishell *minish)
{
	int		status;
	int		pipefd[2];
	pid_t	pids[2];
	t_node	*node;

	if (minish->is_parent == false)
		signal_interceptor(DEFAULT);
	node = *root;
	if (pipe[pipefd] == -1)
		return (PIPE_FAILURE);
	status = first_traversal(&(node->left), minish, pipefd, pids);
	if (status == 0)
		status = second_traversal(&(node->right), minish, pipefd, pids);
	status = wait_childs(pids, 2);
	return (status);
}

int	first_traversal(t_node **node, t_minishell *minish, int pipefd[2],
		int pids[2])
{
	int	status;

	pids[FIRST] = fork();
	if (pids[FIRST] == -1)
		return (FORK_FAILURE);
	if (pids[FIRST] == CHILD)
	{
		signal_interceptor(DEFAULT);
		minish->is_parent = false;
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		{
			close(pipefd[WRITE]);
			exit(DUP_FAILURE);
		}
		close(pipefd[WRITE]);
		status = tree_traverser(node, minish);
		exit(status);
	}
	else
		close(pipefd[WRITE]);
	return (0);
}

int	second_traversal(t_node **node, t_minishell *minish, int pipefd[2],
		int pids[2])
{
	int	status;

	pids[SECOND] = fork();
	if (pids[SECOND] == -1)
		return (FORK_FAILURE);
	if (pids[SECOND] == CHILD)
	{
		signal_interceptor(DEFAULT);
		minish->is_parent = false;
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
		{
			close(pipefd[READ]);
			exit(DUP_FAILURE);
		}
		close(pipefd[READ]);
		status = tree_traverser(node, minish);
		exit(status);
	}
	else
		close(pipefd[READ]);
	return (0);
}
