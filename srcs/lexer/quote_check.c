/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:47:15 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/11 11:26:36 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_inside_quuotes(char *str, int *i, int *quote_type)
{
	if (str[*i] == S_QUOTE && *quote_type == S_QUOTE)
		*quote_type = 0;
	else if (str[*i] == S_QUOTE && *quote_type == 0)
		*quote_type = S_QUOTE;
	else  if (str[*i] == D_QUOTE && *quote_type == D_QUOTE)
		*quote_type = 0;
	else if (str[*i] == D_QUOTE && *quote_type == 0)
		*quote_type = D_QUOTE;
}