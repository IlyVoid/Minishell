/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:51:10 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 12:00:55 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_ops_array(char **arr, char **penv, int *ops)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (arr[++i] != NULL)
	{
		j = 0;
		while (ft_isenv(arr[i][j], &j))
			j++;
		if (arr[i][j] != EQUAL || j == 0)
			ops[i] = EXPORT_ERROR;
		else if (arr[i][j] == EQUAL && j > 0 && arr[i][j - 1] != UNDSCORE)
		{
			if (env_var(penv, arr[i], -1, j + 1) != -1
				|| arg_var(arr, arr[i], i, j + 1) != -1)
				ops[i] = EXPORT_EDIT;
			else
				ops[i] = EXPORT_ADD;
		}
		else
			ops[i] = EXPORT_SKIP;
	}
}

int	check_ops(int *ops, int *i, int *j, int type)
{
	*i = 0;
	*j = -1;
	while (ops[++(*j)])
	{
		if (ops[*j] == type)
			(*i)++;
	}
	if (*i == 0)
		return (1);
	*j = -1;
	return (0);
}
