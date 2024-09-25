/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:50:36 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 16:09:53 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_char(char *str, int *i, int symb)
{
	while (str[*i] == symb && str[*i] != NULL_TERM)
		(*i)++;
}

int	env_var(char **penv, char *var, int i, int j)
{
	while (penv[++i])
	{
		if (ft_strncmp(penv[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}

t_bool	ft_isenv(char c, int *j)
{
	if (*j == 0 && ft_isdigit(c))
		return (false);
	return (ft_isalnum(c) || c == UNDSCORE);
}

int	arg_var(char **arr, char *var, int i, int j)
{
	while (--i >= 0)
	{
		if (ft_strncmp(arr[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}
