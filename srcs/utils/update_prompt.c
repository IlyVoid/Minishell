/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:11:57 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 16:38:41 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prompt_builder(char *dir_name, char **prompt, char *exit_status);

int	fetch_prompt(char **prompt, int exit_status)
{
	char	*cwd;
	char	*dir_name;
	int		status;
	char	*estatus;

	estatus = ft_itoa(exit_status);
	if (!estatus)
		return (MALLOC_ERR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		dir_name = "";
	else
		dir_name = ft_strrchr(cwd, SLASH);
	status = prompt_builder(dir_name, prompt, estatus);
	if (cwd)
		free(cwd);
	free(estatus);
	return (status);
}

int	prompt_builder(char *dir_name, char **prompt, char *exit_status)
{
	int	len;

	len = ft_strlen(dir_name) + ft_strlen(exit_status) + PROMPT_STAT_LEN;
	*prompt = ft_calloc(len + 1, sizeof(char));
	if (!*prompt)
		return (MALLOC_ERR);
	ft_strlcat(*prompt, "d-sh", len);
	ft_strlcat(*prompt, dir_name, len);
	ft_strlcat(*prompt, "[", len);
	ft_strlcat(*prompt, exit_status, len);
	ft_strlcat(*prompt, "] $ ", len);
	return (SUCCESS);
}
