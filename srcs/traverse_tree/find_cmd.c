/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:06:51 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 16:06:52 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_path(char ***path, char **penv, char *cmd);

int	find_cmd(char **cmd, char **penv)
{
	int		status;
	char	**path;

	status = get_path(&path, penv, *cmd);
	if (status != 0)
		return (status);
	status = find_exe(cmd, path);
	ft_free_2d_array(path);
	return (status);
}

static int	get_path(char ***path, char **penv, char *cmd)
{
	char	*str;

	str = NULL;
	while (*penv)
	{
		if (ft_strncmp("PATH=", *penv, 5) == 0)
		{
			str = *penv + 5;
			break ;
		}
		penv++;
	}
	if (!str)
		*path = ft_calloc(1, sizeof(char *));
	else
		*path = ft_split(str, COLON);
	if (!*path)
	{
		print_err_msg(cmd, ": error while allocating\n");
		return (MALLOC_ERR);
	}
	return (0);
}
