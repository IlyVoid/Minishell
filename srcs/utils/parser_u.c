/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:45:06 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/26 21:58:45 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_len_util(char *str, int idx, char quote)
{
	int	a;

	a = 0;
	while (str[idx] && (!ft_is_delimiter(str[idx]) || quote > 0))
	{
		if (str[idx + 1] && ((a % 2 == 0 && str[idx + 1] == ' ') || (quote > 0
					&& quote == str[idx] && str[idx + 1] == ' ')))
		{
			idx++;
			break ;
		}
		if (ft_is_quote(str[idx]))
		{
			quote = str[idx];
			a++;
		}
		idx++;
	}
	return (idx);
}

int	ft_get_word_len(char *str)
{
	int		idx;
	char	is_quote;
	int		a;

	a = 0;
	idx = 0;
	is_quote = 0;
	while (str[idx] != '\0' && (!ft_is_delimiter(str[idx]) || is_quote > 0))
	{
		if (str[idx + 1] && ((a % 2 == 0 && str[idx + 1] == ' ')
				|| (is_quote > 0 && is_quote == str[idx]
					&& str[idx + 1] == ' ')))
		{
			idx++;
			break ;
		}
		if (ft_is_quote(str[idx]))
		{
			is_quote = str[idx];
			a++;
		}
		idx++;
	}
	return (idx);
}

int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}
