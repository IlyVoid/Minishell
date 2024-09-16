/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:45:01 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/16 09:50:03 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_and	*init_t_and(void)
{
	t_and	*node;

	node = (t_and *)ft_calloc(1, sizeof(t_and));
	if (!node)
		return (NULL);
	node->type = T_AND;
	return (node);
}

t_or	*init_t_or(void)
{
	t_or	*node;

	node = (t_or *)ft_calloc(1, sizeof(t_or));
	if (!node)
		return (NULL);
	node->type = T_OR;
	return (node);
}

t_pipe	*init_t_pipe(void)
{
	t_pipe	*node;

	node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->type = T_PIPE;
	return (node);
}

t_bracket	*init_t_br(void)
{
	t_bracket	*node;

	node = (t_bracket *)ft_calloc(1, sizeof(t_bracket));
	if (!node)
		return (NULL);
	node->type = T_BRACKET;
	return (node);
}

t_cmd	*init_t_cmd(void)
{
	t_cmd	*node;

	node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->type = T_CMD;
	return (node);
}
