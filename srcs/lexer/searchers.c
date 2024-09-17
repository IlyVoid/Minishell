/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:23:56 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/17 10:04:52 by brsantsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	br_search(char *str)
{
	int	i;
	int	type_of_quote;
	int	key;

	i = 0;
	type_of_quote = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_inside_quotes(str, &i, &type_of_quote);
		if (!type_of_quote)
		{
			if (str[i] == O_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}

int	redir_search(char *str)
{
	int	i;
	int	type_of_quote;
	int	key;

	i = 0;
	type_of_quote = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_inside_quotes(str, &i, &type_of_quote);
		if (!type_of_quote)
		{
			if (str[i] == REDIR_L || str[i] == REDIR_R)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}
