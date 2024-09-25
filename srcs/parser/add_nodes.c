/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:44:42 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/16 09:48:47 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_or_and_pipe_tree(t_node_info *info, t_node **root, int *hd_num,
		t_minishell *minish)
{
	int	status;

	status = create_tree(info->left_str, &((*root)->left), hd_num, minish);
	if (status == 0)
		status = create_tree(info->right_str, &((*root)->right), hd_num,
				minish);
	return (status);
}

int	add_br(t_node_info *info, t_node **root, int *hd_num, t_minishell *minish)
{
	int	status;

	status = create_tree(info->left_str, &((*root)->left), hd_num, minish);
	return (status);
}

int	add_cmd(t_node_info *info, t_node **root, int *hd_num, t_minishell *minish)
{
	int		status;
	t_redir	*redir_node;
	char	**redirs;

	status = prepare_redirects(info->left_str, hd_num, &redirs, minish);
	if (status != SUCCESS)
		return (status);
	redir_node = init_t_redir();
	if (redir_node == NULL)
	{
		if (redirs)
			ft_free_2d_array(redirs);
		return (MALLOC_ERR);
	}
	redir_node->redirs = redirs;
	((t_cmd *)(*root))->redir = (t_node *)redir_node;
	((t_cmd *)(*root))->cmd = info->right_str;
	return (0);
}

int	add_cmd_br(t_node_info *info, t_node **root, int *hd_num,
		t_minishell *minish)
{
	int		status;
	t_redir	*redir_node;
	char	**redirs;

	status = prepare_redirects(info->left_str, hd_num, &redirs, minish);
	if (status != SUCCESS)
		return (status);
	redir_node = init_t_redir();
	if (redir_node == NULL)
	{
		if (redirs)
			ft_free_2d_array(redirs);
		return (MALLOC_ERR);
	}
	redir_node->redirs = redirs;
	(*root)->left = (t_node *)redir_node;
	status = create_tree(info->right_str, &((*root)->right), hd_num, minish);
	return (status);
}
