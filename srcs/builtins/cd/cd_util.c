/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:11:48 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 16:24:36 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_env_oldpwd(t_minishell *minish);

void	struct_update_pwd_and_full_oldpwd(char *new_pwd, t_minishell *minish)
{
	if (minish->oldpwd)
		free(minish->oldpwd);
	minish->oldpwd = ft_strdup(minish->pwd);
	if (!(minish->oldpwd))
	{
		print_err_msg("cd", ": malloc error occured. "
			"Correct behavior is not guaranteed anymore\n");
		minish->exit_status = MALLOC_ERR;
		return ;
	}
	update_env_oldpwd(minish);
	if (minish->exit_status != SUCCESS)
		return ;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_err_msg("cd", ": getcwd error occured. "
			"Correct behavior is not guaranteed anymore\n");
		minish->exit_status = GETCWD_ERROR;
		return ;
	}
	free(minish->pwd);
	minish->pwd = new_pwd;
}

void	cd_precheck(char **arr, t_minishell *minish)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		if (arr[0][1] == DASH && arr[0][2] == NULL_TERM)
			return ;
		arr[0][2] = NULL_TERM;
		arg_err_msg("cd: `", arr[0], "': options are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
	}
}

void	update_env_pwd(t_minishell *minish, int pos, char *cwd, char *temp)
{
	pos = env_var(minish->env, "PWD=", -1, 4);
	if (pos != -1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			print_err_msg("cd", ": getcwd error occured. "
				"Correct behavior is not guaranteed anymore\n");
			minish->exit_status = GETCWD_ERROR;
			return ;
		}
		temp = ft_strjoin("PWD=", cwd);
		if (!temp)
		{
			print_err_msg("cd", ": malloc error occured. "
				"Correct behavior is not guaranteed anymore\n");
			free(cwd);
			minish->exit_status = MALLOC_ERR;
			return ;
		}
		free((minish->env)[pos]);
		(minish->env)[pos] = temp;
		free(cwd);
	}
}

static int	oldpwd_init_when_no_oldpwd_exists(int i, t_minishell *minish)
{
	int		len;
	char	**new_env;

	len = ft_arrlen((void **)(minish->env));
	if (add_to_env_list_new_env((minish->env), &new_env, &i, &len)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len] = ft_strjoin("OLDPWD=", minish->pwd);
	if (!new_env[len])
		return (MALLOC_ERR);
	minish->env = new_env;
	return (SUCCESS);
}

void	update_env_oldpwd(t_minishell *minish)
{
	int		pos_pwd;
	int		pos_oldpwd;
	char	*temp;

	pos_oldpwd = env_var(minish->env, "OLDPWD=", -1, 7);
	pos_pwd = env_var(minish->env, "PWD=", -1, 4);
	if (pos_oldpwd != -1)
	{
		temp = ft_strjoin("OLDPWD=", minish->pwd);
		if (!temp)
		{
			minish->exit_status = MALLOC_ERR;
			return ;
		}
		free((minish->env)[pos_oldpwd]);
		(minish->env)[pos_oldpwd] = temp;
	}
	else if (pos_oldpwd == -1 && pos_pwd != -1
		&& minish->is_oldpwd_unset == false)
		minish->exit_status = oldpwd_init_when_no_oldpwd_exists(1, minish);
}
