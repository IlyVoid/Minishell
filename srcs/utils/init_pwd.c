/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:02:54 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 01:14:06 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_pwd_if_exists(int pos, char ***penv, char **pwd)
{
	char	*tmp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("\033[0;31md-sh:\033[0;0m getcwd");
		return (GETCWD_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (!*pwd)
	{
		free(cwd);
		return (MALLOC_ERR);
	}
	tmp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!tmp)
		return (MALLOC_ERR);
	free((*penv)[pos]);
	(*penv)[pos] = tmp;
	return (SUCCESS);
}

static int	init_pwd_if_none_exist(char ***penv, char **pwd)
{
	int		len;
	char	*cwd;
	char	**env_new;
	int		i;

	i = 1;
	if (add_to_env_list_env_new(*penv, &env_new, &i, &len) == MALLOC_ERR)
		return (MALLOC_ERR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("\033[0;31md-sh: \033[0;0m getcwd");
		return (GETCWD_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (*pwd)
		env_new[len] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd || !env_new[len])
		return (MALLOC_ERR);
	*penv = env_new;
	return (SUCCESS);
}

int	init_pwd(char ***penv, char **pwd)
{
	int		pos;
	int		status;

	pos = env_var(*penv, "PWD=", -1, 4);
	if (pos == -1)
		status = init_pwd_if_none_exist(penv, pwd);
	else
		status = init_pwd_if_exists(pos, penv, pwd);
	return (status);
}
