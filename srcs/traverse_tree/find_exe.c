/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:48:23 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/29 13:49:49 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_provided_path(char *cmd_name, char **cmd_in_path);
static int	find_cmd_in_path(char *char_name, char **paths, char **cmd_in_path);
static char	*allocate_cmd_string(char *cmd_name, int *length, char **paths);
static int	check_cmd_in_path(char **selection, int len, char *cmd_name,
				char *path);

int	find_exe(char **cmnd, char **paths)
{
	int		status;
	char	*cmd_in_path;

	cmd_in_path = NULL;
	if (ft_strchr(cmnd[0], '/') == NULL)
	{
		status = find_cmd_in_path(cmnd[0], paths, &cmd_in_path);
		if (status == CMD_PD_FAILURE)
			print_err_msg(cmnd[0], " : Permission denied\n");
	}
	else
		status = check_provided_path(cmnd[0], &cmd_in_path);
	if (status == 0)
	{
		if (ft_strchr(cmnd[0], '/') == NULL)
			free(cmnd[0]);
		cmnd[0] = cmd_in_path;
	}
	return (status);
}

static int	check_provided_path(char *cmd_name, char **cmd_in_path)
{
	struct stat	st;

	if (access(cmd_name, F_OK) != 0)
	{
		print_err_msg(cmd_name, ": No such file or directory\n");
		return (CMD_NF_FAILURE);
	}
	stat(cmd_name, &st);
	if (access(cmd_name, X_OK) != 0)
	{
		print_err_msg(cmd_name, ": Permission denied\n");
		return (CMD_PD_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_err_msg(cmd_name, ": is a directory\n");
		return (CMD_PD_FAILURE);
	}
	*cmd_in_path = cmd_name;
	return (0);
}

static int	find_cmd_in_path(char *cmd_name, char **paths, char **cmd_in_path)
{
	int		status;
	char	*selection;
	int		len;
	int		i;

	selection = allocate_cmd_string(cmd_name, &len, paths);
	if (!selection)
		return (MALLOC_ERR);
	i = 0;
	while (paths[i])
	{
		status = check_cmd_in_path(&selection, len, cmd_name, paths[i]);
		if (status != 1)
		{
			if (status == 0)
				*cmd_in_path = selection;
			else if (status == CMD_PD_FAILURE)
				free(selection);
			return (status);
		}
		i++;
	}
	free(selection);
	print_err_msg(cmd_name, ": command not found\n");
	return (CMD_NF_FAILURE);
}

static char	*allocate_cmd_string(char *cmd_name, int *len, char **paths)
{
	char	*cmd;
	int		current_len;
	int		i;

	i = 0;
	*len = 0;
	while (paths[i])
	{
		current_len = ft_strlen(paths[i]);
		if (current_len > *len)
			*len = current_len;
		i++;
	}
	*len += ft_strlen(cmd_name) + 1 + 1;
	cmd = (char *)ft_calloc(*len, sizeof(char));
	if (!cmd)
	{
		print_err_msg(cmd_name, ": allocation error occured\n");
		return (NULL);
	}
	return (cmd);
}

static int	check_cmd_in_path(char **selection, int len, char *cmd_name,
		char *path)
{
	char		*temp;
	struct stat	st;

	temp = *selection;
	ft_memset(temp, 0, len);
	ft_strlcat(temp, path, len);
	ft_strlcat(temp, "/", len);
	ft_strlcat(temp, cmd_name, len);
	if (access(temp, F_OK) == 0)
	{
		stat(temp, &st);
		if (S_ISDIR(st.st_mode))
			return (1);
		if (access(temp, X_OK) == 0)
			return (0);
		else
			return (CMD_PD_FAILURE);
	}
	else
		return (1);
}
