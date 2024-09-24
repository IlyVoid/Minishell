/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:14:43 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:29:30 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*br_val(char *str, t_bool *status);

char	*cmd_val(char *str, t_bool *status)
{
	char	*next_token;

	next_token = simple_cmd_val(str, status);
	if (next_token != str || *status == false)
		return (next_token);
	else if (*str == O_ROUND)
	{
		if (string_is_empty(str + 1) == true)
		{
			*status = false;
			return (str + 1);
		}
		next_token = br_val(next_token, status);
	}
	return (next_token);
}

static char	*br_val(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = and_or_val(str, status);
	if (*status == false)
		return (next_token);
	if (*next_token != C_ROUND)
	{
		*status = false;
		return (next_token);
	}
	next_token++;
	while (ft_isspace(*next_token))
		next_token++;
	next_token = redir_val(next_token, status);
	return (next_token);
}
