/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:47:35 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 16:34:16 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	exec_export(char ***env_new, char **arr, t_minishell *minish,
	int *ops)
{
	if (add_to_env_list(env_new, arr, minish, ops) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (*env_new)
	{
		if (edit_env_list(env_new, arr, ops, minish) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (edit_env_list(&(minish->env), arr, ops, minish) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (exec_other(arr, ops));
}

static void	export_with_args(char **arr, t_minishell *minish)
{
	char	**env_new;
	int		*ops;

	env_new = NULL;
	ops = ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(int));
	if (!ops)
	{
		minish->exit_status = MALLOC_ERR;
		return ;
	}
	create_ops_array(arr, minish->env, ops);
	minish->exit_status = exec_export(&env_new, arr, minish, ops);
	if (minish->exit_status == MALLOC_ERR)
	{
		free(ops);
		return ;
	}
	if (env_new)
		minish->env = env_new;
	free(ops);
}

static void	export_without_args_print(char **penv_sorted, int i, int j)
{
	j = 0;
	if (penv_sorted[i][0] == UNDSCORE && penv_sorted[i][1] == EQUAL)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (penv_sorted[i][j] != EQUAL && penv_sorted[i][j] != NULL_TERM)
		ft_putchar_fd(penv_sorted[i][j++], STDOUT_FILENO);
	if (ft_strcmp(penv_sorted[i], "OLDPWD=") == 0)
	{
		ft_putchar_fd(NL, STDOUT_FILENO);
		return ;
	}
	ft_putchar_fd(EQUAL, STDOUT_FILENO);
	ft_putchar_fd(D_QUOTE, STDOUT_FILENO);
	j++;
	ft_putstr_fd(penv_sorted[i] + j, STDOUT_FILENO);
	ft_putchar_fd(D_QUOTE, STDOUT_FILENO);
	ft_putchar_fd(NL, STDOUT_FILENO);
}

static void	export_without_args(t_minishell *minish, int i, int j)
{
	char	**penv_sorted;

	if (minish->is_oldpwd_unset == false
		&& env_var(minish->env, "OLDPWD=", -1, 7) == -1)
	{
		if (init_var_if_none_exist(&minish->env, 1, "OLDPWD=") != 0)
		{
			minish->exit_status = MALLOC_ERR;
			return ;
		}
	}
	penv_sorted = sort_str_arr(minish->env, ft_arrlen((void **)minish->env));
	if (!penv_sorted)
	{
		minish->exit_status = MALLOC_ERR;
		return ;
	}
	while (penv_sorted[++i])
		export_without_args_print(penv_sorted, i, j);
	exec_unset(&(minish->env), env_var(minish->env, "OLDPWD=", -1, 7), 0);
	free(penv_sorted);
}

void	run_export(char **arr, t_minishell *minish)
{
	int		arr_len;

	arr_len = ft_arrlen((void **)arr);
	if (arr_len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		arg_err_msg("env: `", arr[0], "': options are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
	}
	else if (arr_len > 0)
		export_with_args(arr, minish);
	else
		export_without_args(minish, -1, 0);
}
