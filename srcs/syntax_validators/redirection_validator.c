/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_validator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:13:49 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/28 09:31:03 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*validate_redirect(char *str, t_bool *status)
{
	char	*next_token;

	if (ft_strncmp(">>", str, 2) == 0)
		str += 2;
	else if (ft_strncmp("<<", str, 2) == 0)
		str += 2;
	else if (ft_strncmp(">", str, 1) == 0)
		str += 1;
	else if (ft_strncmp("<", str, 1) == 0)
		str += 1;
	else
		return (str);
	if (ft_isspace(*str))
		str++;
	next_token = validate_word(str, status);
	if (next_token == str)
		*status = false;
	if (*status == false || *next_token == C_ROUND)
		return (next_token);
	while (ft_isspace(*next_token))
		next_token++;
	next_token = validate_redirect(next_token, status);
	return (next_token);
}
