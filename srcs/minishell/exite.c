/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:35:14 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/26 21:51:25 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_env *env)
{
	free_string(env->front);
	free_string(env->back);
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free_string(tmp->front);
		free_string(tmp->back);
		free(tmp);
	}
}

void	ft_exit(char *str, int status, t_data	*g_data)
{
	free_env(g_data->environmental);
	free_matrix(g_data->env);
	free(g_data);
	if (status == 0)
		ft_putstr_fd(str, 1);
	else if (status == 1)
		ft_putstr_fd(str, 1);
	exit(0);
}
