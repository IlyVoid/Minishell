/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:42:01 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 16:45:41 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tree_traverser(t_node **root, t_minishell *minish)
{
	int	type;
	int	status;

	status = true;
	type = (*root)->type;
	if (type == T_AND)
		status = and_traverser(root, minish);
	else if (type == T_OR)
		status = or_traverser(root, minish);
	else if (type == T_PIPE)
		status = pipe_traverser(root, minish);
	else if (type == T_BRACKET)
		status = bracket_traverser(root, minish);
	else if (type == T_CMD_BR)
		status = cmd_br_traverser(root, minish);
	else if (type == T_CMD)
		status = cmd_traverser(((t_cmd *)*root)->cmd,
				((t_redir *)((t_cmd *)*root)->redir)->redirs,
				minish);
	free_tree(root);
	return (status);
}

int	and_traverser(t_node **root, t_minishell *minish)
{
	int		status;
	t_node	*node;

	node = *root;
	status = tree_traverser(&(node->left), minish);
	if (status == 0)
		status = tree_traverser(&(node->right), minish);
	return (status);
}

int	or_traverser(t_node **root, t_minishell *minish)
{
	int		status;
	t_node	*node;

	node = *root;
	status = tree_traverser(&(node->left), minish);
	if (status != 0)
		status = tree_traverser(&(node->right), minish);
	return (status);
}
