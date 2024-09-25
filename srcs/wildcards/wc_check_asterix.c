/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_check_asterix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:10:47 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:11:26 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	if_asterix_in_arr(char **arr, int i, int j)
{
	int	quote_type;

	quote_type = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] != NULL_TERM)
		{
			check_inside_quotes(arr[i], &j, &quote_type);
			if (!quote_type)
			{
				if (arr[i][j++] == ASTERIX)
					return (true);
			}
			else
				j++;
		}
		i++;
	}
	return (false);
}
