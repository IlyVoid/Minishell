/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_runner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:40:49 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/31 18:46:42 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_without_redir(char **cmd, t_minishell *minish, int cmd_type);
int	run_with_redir(char **cmd, char **redir, t_minishell *minish, int cmd_type);
int	cpy_fd_std(int *in_fd, int *out_fd, char *cmd);

