/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:50:28 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 01:58:10 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sub_arr_sort(char *av[], int size)
{
	int		j;
	int		k;
	char	*tmp;

	j = 1;
	while (j < size)
	{
		if (ft_strcmp(*av, av[j]) > 0)
		{
			k = j;
			tmp = av[j];
			while (k != 0)
			{
				av[k] = av[k - 1];
				k--;
			}
			*av = tmp;
		}
		j++;
	}
}

char	**sort_str_arr(char **av, int size)
{
	int		i;
	char	**res;

	res = (char **)ft_calloc(size + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy((void *)res, (void *)av, sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		sub_arr_sort(res + i, size - i);
		i++;
	}
	return (res);
}
