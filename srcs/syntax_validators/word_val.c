/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:33:35 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:02:32 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*quote_val(char *str, t_bool *status);

char	*word_val(char *str, t_bool *status)
{
	char	*special_char;

	special_char = "&|<>() '\"";
	while (*str && ft_strchr(special_char, *str) == NULL)
		str++;
	if (*str == S_QUOTE || *str == D_QUOTE)
		str = quote_val(str, status);
	return (str);
}

static char	*quote_val(char *str, t_bool *status)
{
	if (*str == D_QUOTE)
	{
		str++;
		while (*str != NULL_TERM && *str != D_QUOTE)
			str++;
	}
	else if (*str == S_QUOTE)
	{
		str++;
		while (*str != NULL_TERM && *str != S_QUOTE)
			str++;
	}
	if (*str == NULL_TERM)
	{
		*status = false;
		return (str);
	}
	return (str + 1);
}
