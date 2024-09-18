/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:44:26 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/18 13:56:49 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_block(t_node_info **node, char *str, int type)
{
	if (redir_search(str))
		return (put_info_cmd_node(node, str, type));
	else
		return (put_simple_cmd_node(node, str, T_CMD));
	return (0);
}

int	cmd_br_block(t_node_info **node, char *str, int type)
{
	if (br_search(str))
		return (put_info_cmd_br_node(node, str, type));
	return (0);
}
