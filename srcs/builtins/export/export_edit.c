/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:01:18 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/23 12:05:00 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	edit_env_list_pwd(int position, char *str, char **result,
	t_minishell *minish)
{
	char	*var_new;

	free(minish->pwd);
	minish->pwd = ft_strdup(str + 4);
	if (!minish->pwd)
		return (MALLOC_ERR);
	var_new = ft_strdup(str);
	if (var_new == NULL)
	{
		if (ft_strncmp(result[position], "PWD=", 4) == 0)
			print_err_msg("PWD", ": malloc error occured. "
				"Correct behavior is not guaranteed anymore\n");
		return (MALLOC_ERR);
	}
	free(result[position]);
	result[position] = var_new;
	return (SUCCESS);
}

static int	edit_env_list_subs(char *str, char **result,
	t_minishell *minish)
{
	int		position;
	char	*var_new;
	int		i;

	i = 0;
	while (str[i] != EQUAL)
		i++;
	position = env_var(result, str, -1, i);
	if (position == -1)
	{
		print_err_msg("EXPORT", ": add to env list error occured. "
			"Correct behavior is not guaranteed anymore\n");
		return (MALLOC_ERR);
	}
	if (ft_strncmp(result[position], "PWD=", 4) == 0)
		return (edit_env_list_pwd(position, str, result, minish));
	var_new = ft_strdup(str);
	if (var_new == NULL)
		return (MALLOC_ERR);
	free(result[position]);
	result[position] = var_new;
	return (SUCCESS);
}

int	edit_env_list(char ***env_new, char **arr, int *ops,
	t_minishell *minish)
{
	int		i;
	int		j;
	char	**result;

	result = *env_new;
	if (check_ops(ops, &i, &j, EXPORT_EDIT))
		return (SUCCESS);
	while (ops[++j])
	{
		if (ops[j] == EXPORT_EDIT)
		{
			if (edit_env_list_subs(arr[j], result, minish) == MALLOC_ERR)
				return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}
