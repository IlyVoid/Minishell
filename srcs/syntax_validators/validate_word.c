/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:33:35 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/28 10:05:22 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*validate_quotes(char *str, t_bool *status);

char	*validate_word(char *str, t_bool *status)
{
	char	*special_char;

	special_char = "&|<>() '\"";
	while (*str && ft_strchr(special_char, *str) == NULL)
		str++;
	if (*str == S_QUOTE || *str == D_QUOTE)
		str = validate_quotes(str, status);
	return (str);
}

static char	*validate_quotes(char *str, t_bool *status)
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
		*status == false;
		return (str);
	}
	return (str + 1);
}
