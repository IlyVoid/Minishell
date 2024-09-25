/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:14:14 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 18:37:21 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

void	kill_minish(t_minishell **minish, int status);

void	init_minish(t_minishell **minish)
{
	extern char	**envi;
	int			status;

	status = 0;
	*minish = ft_calloc(1, sizeof(t_minishell));
	if (!*minish)
		status = MALLOC_ERR;
	if (status == 0)
	{
		(*minish)->env = cpy_env(envi);
		if (!(*minish)->env)
			status = MALLOC_ERR;
	}
	if (status == 0)
		status = init_pwd(&((*minish)->env), &((*minish)->pwd));
	if (status == 0)
		status = init_shlvl(&((*minish)->env));
	if (status == 0)
		init_hst(minish);
	(*minish)->is_parent = true;
	g_sgnl = 0;
	if (status != 0)
		kill_minish(minish, status);
}

void	kill_minish(t_minishell **minish, int status)
{
	free_minish(*minish);
	ft_putstr_fd("\033[0;31md-sh:\033[0;0m can't initialize "
		"t_minishell structure\n",
		STDERR_FILENO);
	exit(status);
}
