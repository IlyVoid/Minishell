/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_constructor1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:45:06 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/16 09:50:34 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_br	*init_t_cmd_br(void)
{
	t_cmd_br	*node;

	node = (t_cmd_br *)ft_calloc(1, sizeof(t_cmd_br));
	if (!node)
		return (NULL);
	node->type = T_CMD_BR;
	return (node);
}

t_redir	*init_t_redir(void)
{
	t_redir	*node;

	node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = T_REDIR;
	return (node);
}
