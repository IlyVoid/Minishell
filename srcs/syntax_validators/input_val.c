/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:39:36 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 15:43:23 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_val(char *str)
{
	char	*next_token;
	t_bool	status;

	status = true;
	while (ft_isspace(*str))
		str++;
	if (*str == NULL_TERM)
		return (SUCCESS);
	next_token = and_or_val(str, &status);
	if (*next_token != NULL_TERM || status == false)
	{
		syntax_err_msg(next_token);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
