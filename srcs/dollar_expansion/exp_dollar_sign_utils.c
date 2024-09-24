/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar_sign_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:54:07 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 20:55:27 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_env_exp_module(char **penv, char *var, int i, int j)
{
	while (penv[++i])
	{
		if (ft_strncmp(penv[i], var, j) == 0)
		{
			if (penv[i][j] == EQUAL)
				return (i);
		}
	}
	return (NOT_FOUND);
}

void	index_quotes(char *str, int i, int *s_quote, int *d_quote)
{
	if (str[i] == S_QUOTE && !(*s_quote) && !(*d_quote))
		*s_quote = 1;
	else if (str[i] == D_QUOTE && !(*d_quote) && !(*s_quote))
		*d_quote = 1;
	else if (str[i] == S_QUOTE && !(*s_quote) && *d_quote == 1)
		*s_quote = 2;
	else if (str[i] == D_QUOTE && !(*d_quote) && *s_quote == 1)
		*d_quote = 2;
	else if (str[i] == S_QUOTE && *s_quote)
		*s_quote = 0;
	else if (str[i] == D_QUOTE && *d_quote)
		*d_quote = 0;
}
