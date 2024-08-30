/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:59:34 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 16:01:54 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	string_is_empty(char *str)
{
	if (ft_strlen(str) == 0)
		return (true);
	while (ft_isspace(*str))
		str++;
	return (*str == NULL_TERM);
}
