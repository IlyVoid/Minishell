/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:02:15 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/17 10:03:31 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	and_if_condition_block(t_node_info **node, char *str, int type, int i)
{
	if (str[i] == AND && str[i - 1] == AND)
	{
		if (check_round_br(str, i) && check_quote(str, i, S_QUOTE)
			&& check_quote(str, i, D_QUOTE))
			return (put_info_and_or_pipe_node(node, str, i, T_AND));
		else
			return (lexer(node, str, type, i - 2));
	}
	else if (str[i] == PIPE && str[i - 1] == PIPE)
	{
		if (check_round_br(str, i) && check_quote(str, i, S_QUOTE)
			&& check_quote(str, i, D_QUOTE))
			return (put_info_and_or_pipe_node(node, str, i, T_AND));
		else
			return (lexer(node, str, type, i - 2));
	}
	return (0);
}

int	pipe_block(t_node_info **node, char *str, int type, int i)
{
	if (str[i] == PIPE)
	{
		if (check_round_br(str, i) && check_quote(str, i, S_QUOTE)
			&& check_quote(str, i, D_QUOTE))
			return (put_info_and_or_pipe_node(node, str, i, T_AND));
		else
			return (lexer(node, str, type, i - 1));
	}
	return (0);
}

int	br_block(t_node_info **node, char *str, int type)
{
	if (first_char_is_br_space_excluded(str)
		&& last_char_is_br_space_excluded(str))
		return (put_info_bracket_node(node, str, type));
	return (0);
}
