/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:25:23 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 16:09:17 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_search_pos(char ***penv, char *var, int i)
{
	char	**env_new;
	int		pos;

	env_new = *penv;
	while (env_new[++i])
	{
		pos = env_var(env_new, var, i - 1, ft_strlen(var));
		if (pos == -1)
			return (-1);
		else if (env_new[pos][ft_strlen(var)] == EQUAL)
				return (pos);
		else
		{
			i += pos;
			continue ;
		}
	}
	return (-1);
}

void	exec_unset(char ***penv, int pos, int i)
{
	char	**env_new;

	env_new = *penv;
	if (env_new[i + 1] == NULL)
		return ;
	while (i < pos)
		i++;
	if (i == pos)
		free(env_new[i]);
	while (env_new[i])
	{
		env_new[i] = env_new[i + 1];
		i++;
	}
	env_new[i] = NULL;
	*penv = env_new;
}

static void	iterate_args(char **arr, t_minishell *minish, int *j)
{
	int	pos;
	int	i;

	i = 0;
	while (arr[*j][i] != NULL_TERM)
	{
		if (!ft_isenv(arr[*j][i], &i))
		{
			arg_err_msg("unset: `", arr[*j], "': not a valid identifier\n");
			minish->exit_status = GENERIC_ERROR;
			return ;
		}
		i++;
	}
	if (arr[*j][0] == UNDSCORE && arr[*j][1] == NULL_TERM)
		return ;
	pos = env_search_pos(&(minish->env), arr[*j], -1);
	if (pos == -1)
		return ;
	else
		exec_unset(&(minish->env), pos, 0);
	return ;
}

void	run_unset(char **arr, t_minishell *minish)
{
	int	j;
	int	len;

	j = -1;
	len = ft_arrlen((void **)arr);
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		arg_err_msg("unset: `", arr[0], "': options are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
	}
	else if (len > 0)
	{
		while (arr[++j])
		{
			if (ft_strcmp(arr[j], "OLDPWD") == 0)
				minish->is_oldpwd_unset = true;
			iterate_args(arr, minish, &j);
		}
	}
}
