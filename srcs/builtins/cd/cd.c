/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:25:03 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 18:21:31 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h>

static void	cd_oldpwd_handler(t_minishell *minish)
{
	int	env_vars;

	env_vars = env_var(minish->env, "OLDPWD=", -1, 7);
	if (env_vars == -1)
	{
		print_err_msg("cd: ", "OLDPWD not set\n");
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (chdir((minish->env)[env_vars] + 7) != 0)
	{
		perror_err_msg("cd: ", (minish->env)[env_vars] + 7);
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else
		printf("%s\n", (minish->env)[env_vars] + 7);
}

static void	handle_cd_home(t_minishell *minish)
{
	int		env_variable;

	env_variable = env_var(minish->env, "HOME=", -1, 5);
	if (env_variable == -1)
	{
		print_err_msg("cd: ", "HOME not set\n");
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (chdir((minish->env)[env_variable] + 5) != 0)
	{
		perror_err_msg("cd: ", (minish->env)[env_variable] + 5);
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
}

void	run_cd(char **arr, t_minishell *minish, int status)
{
	cd_precheck(arr, minish);
	if (minish->exit_status != SUCCESS)
		return ;
	if (ft_arrlen((void **)arr) == 0 || !ft_strncmp(arr[0], "--", 2))
		handle_cd_home(minish);
	else if (!ft_strncmp(arr[0], "-", ft_strlen(arr[0]))
		&& ft_strlen(arr[0]) > 0)
		cd_oldpwd_handler(minish);
	else if (ft_strlen(arr[0]) == 0)
		status = chdir(".");
	else
		status = chdir(arr[0]);
	if (status != 0)
	{
		perror_err_msg("cd: ", arr[0]);
		minish->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (minish->exit_status != SUCCESS)
		return ;
	struct_update_pwd_and_full_oldpwd(NULL, minish);
	if (minish->exit_status != SUCCESS)
		return ;
	update_env_pwd(minish, 0, NULL, NULL);
}
