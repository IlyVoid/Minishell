/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:59:43 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:08:28 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*and_or_val(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = pipe_val(str, status);
	if (*status == false)
		return (next_token);
	if ((ft_strncmp("&&", next_token, 2) == 0 || ft_strncmp("||", next_token,
				2) == 0))
	{
		next_token += 2;
		if (string_is_empty(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		next_token = and_or_val(next_token, status);
	}
	return (next_token);
}
