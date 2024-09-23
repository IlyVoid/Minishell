/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:55:47 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 11:59:09 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	add_to_env_list_pwd_cases(char *str, t_minishell *minish)
{
	char	*temp_pwd;

	if (ft_strncmp(str, "OLDPWD=", 7) == 0)
		minish->is_oldpwd_unset = false;
	if (ft_strncmp(str, "PWD=", 4) == 0)
	{
		temp_pwd = ft_strdup(str + 4);
		if (!temp_pwd)
		{
			print_err_msg("PWD", ": malloc error occured. "
				"Correct behavior is not guaranteed anymore\n");
			return (MALLOC_ERR);
		}
		free(minish->pwd);
		minish->pwd = temp_pwd;
	}
	return (SUCCESS);
}

int	add_to_env_list_env_new(char **penv, char ***result,
	int *i, int *len)
{
	*len = ft_arrlen((void **)penv);
	*result = (char **)ft_calloc(*len + *i + 1, sizeof(char *));
	if (!*result)
		return (MALLOC_ERR);
	ft_memcpy((void *)*result, (void *)penv, *len * sizeof(char *));
	free(penv);
	*i = 0;
	return (SUCCESS);
}

int	add_to_env_list(char ***env_new, char **arr, t_minishell *minish,
	int *ops)
{
	int		i;
	int		j;
	int		len;
	char	*var_new;

	if (check_ops(ops, &i, &j, EXPORT_ADD))
		return (SUCCESS);
	if (add_to_env_list_env_new(minish->env, env_new, &i, &len) == MALLOC_ERR)
		return (MALLOC_ERR);
	while (ops[++j])
	{
		if (ops[j] == EXPORT_ADD)
		{
			if (add_to_env_list_pwd_cases(arr[j], minish) == MALLOC_ERR)
				return (MALLOC_ERR);
			var_new = ft_strdup(arr[j]);
			if (var_new == NULL)
			{
				ft_free_2d_array(*env_new);
				return (MALLOC_ERR);
			}
			env_new[0][len + i++] = var_new;
		}
	}
	return (SUCCESS);
}
