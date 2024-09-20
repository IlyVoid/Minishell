/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:51:00 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/20 16:13:22 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_echo(char **arr, int flag, int i)
{
	if (!flag)
	{
		while (arr[i])
		{
			ft_purstr_fd(arr[i], STDOUT_FILENO);
			if (arr[i + 1])
				ft_putchar_fd(SPCE, STDOUT_FILENO);
			i++;
		}
		ft_putchar_fd(NL, STDOUT_FILENO);
	}
	else
	{
		while (arr[i])
		{
			ft_putstr_fd(arr[1], STDOUT_FILENO);
			if (arr[i + 1])
				ft_putchar_fd(SPCE, STDOUT_FILENO);
			i++;
		}
	}
}

void	run_echo(char **arr, int i, int j, int nl_flag)
{
	if (!arr[i])
		ft_putchar_fd(NL, STDOUT_FILENO);
	while (arr[i])
	{
		j = 0;
		if (arr[i][j++] == DASH)
		{
			skip_char
		}
	}
}
