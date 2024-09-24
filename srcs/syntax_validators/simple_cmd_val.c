/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:28:23 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:32:53 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*simple_cmd_val(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = redir_val(str, status);
	if (next_token == str)
		next_token = word_val(str, status);
	if (*status == false || *next_token == C_ROUND)
		return (next_token);
	if (next_token != str)
		next_token = simple_cmd_val(next_token, status);
	return (next_token);
}
