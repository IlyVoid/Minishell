/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:05:44 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 12:07:59 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_for_errors(char **arr, int *ops)
{
	int	j;

	j = -1;
	while (arr[++j])
	{
		if (ops[j] == 0)
			return (GENERIC_ERROR);
	}
	return (SUCCESS);
}


int	exec_other(char **arr, int *ops)
{
	int		j;
	int		i;

	j = -1;
	while (arr[++j])
	{
		if (ops[j] == EXPORT_ERROR)
		{
			i = 0;
			if (ft_isdigit(arr[j][i]))
				ops[j] = 0;
			while (ft_isenv(arr[j][i], &i))
				i++;
			if (arr[j][i] != NULL_TERM)
				ops[j] = 0;
		}
		if (ops[j] == 0)
		{
			arg_err_msg("export: `", arr[j],
				"': not a valid identifier\n");
		}
	}
	return (check_for_errors(arr, ops));
}
