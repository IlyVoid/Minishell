/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:09:15 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:14:04 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pipe_val(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = cmd_val(str, status);
	if (next_token == str)
		*status = false;
	if (*status == false)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE)
	{
		next_token++;
		if (string_is_empty(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		next_token = pipe_val(next_token, status);
	}
	return (next_token);
}
