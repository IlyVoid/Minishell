/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:44:57 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/11 10:44:59 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_node **root)
{
	if (*root == NULL)
		return ;
	if ((*root)->type == T_BRACKET)
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
	}
	else if ((*root)->type == T_REDIR)
	{
		if (((t_redir *)(*root))->redirs)
			ft_free_2d_array(((t_redir *)(*root))->redirs);
	}
	else if ((*root)->type == T_CMD)
	{
		free_tree(&((t_cmd *)(*root))->redir);
	}
	else
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
		if ((*root)->right)
			free_tree(&((*root)->right));
	}
	free(*root);
	*root = NULL;
}
