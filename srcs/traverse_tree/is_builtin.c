/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:07:06 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 16:07:07 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (C_EMPTY);
	if (string_is_empty(cmd))
		return (C_BLANK);
	if (ft_strncmp(cmd, "echo", ECHO_LENGTH) == 0)
		return (C_ECHO);
	if (ft_strncmp(cmd, "cd", CD_LENGTH) == 0)
		return (C_CD);
	if (ft_strncmp(cmd, "pwd", PWD_LENGTH) == 0)
		return (C_PWD);
	if (ft_strncmp(cmd, "export", EXPORT_LENGTH) == 0)
		return (C_EXPORT);
	if (ft_strncmp(cmd, "unset", UNSET_LENGTH) == 0)
		return (C_UNSET);
	if (ft_strncmp(cmd, "env", ENV_LENGTH) == 0)
		return (C_ENV);
	if (ft_strncmp(cmd, "exit", EXIT_LENGTH) == 0)
		return (C_EXIT);
	return (NOT_BUILTIN);
}
