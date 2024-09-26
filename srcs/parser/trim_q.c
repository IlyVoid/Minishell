/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:45:01 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/26 21:55:17 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_trim_len(char *str, char *quote, int i, int len)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			*quote = str[i];
			i++;
			while (str[i] != '\0')
			{
				if (str[i] == *quote)
					break ;
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_trim_quotes(char *str, int i, int len)
{
	char	quote;
	char	*res;

	len = ft_get_trim_len(str, &quote, 0, 0);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] != '\0')
			{
				if (str[i] == quote)
					break ;
				res[len++] = str[i++];
			}
		}
		else
			res[len++] = str[i++];
	}
	res[len] = '\0';
	return (res);
}
