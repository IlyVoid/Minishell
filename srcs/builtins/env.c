/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:03:09 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 14:36:54 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env(char **env, int j)
{
	while (env[++j])
		printf("%s\n", env[j]);
}

void	run_env(char **arr, t_minishell *minish)
{
	char	**env_new;
	int		len;

	len = ft_arrlen((void **)arr);
	env_new = minish->env;
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		arg_err_msg("env: `", arr[0], "': options are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
	}
	else if (len > 0)
	{
		arg_err_msg("env: `", arr[0], "': arguments are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
	}
	else
		print_env(env_new, -1);
}
