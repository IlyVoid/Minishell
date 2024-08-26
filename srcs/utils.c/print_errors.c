/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:37:42 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/26 16:44:05 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_err_msg(char *cmd, char *msg)
{
	cmd = ft_strjoin("\033[0;31md-sh: \033[0;0m", cmd);
	if (!cmd)
		return ;
	msg = ft_strjoin(cmd, msg);
	free(cmd);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

void	shlvl_warn_msg(int number)
{
	char	*first_part;
	char	*num;
	char	*first_num_part;
	char	*msg;

	first_part = "\033[0;31md-sh: \033[0;0mwarning: minishell level (";
	num = ft_itoa(number);
	if (!num)
		return ;
	first_num_part = ft_strjoin(first_part, num);
	free(num);
	if (!first_num_part)
		return ;
	msg = ft_strjoin(first_num_part, msg);
	free(first_num_part);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

void	perror_err_msg(char *cmd, char *arg)
{
	cmd = ft_strjoin("\033[0;31md-sh: \033[0;0m", cmd);
	if (!cmd)
		return ;
	arg = ft_strjoin(cmd, arg);
	free(cmd);
	if (!arg)
		return ;
	perror(arg);
	free(arg);
}

void	arr_err_msg(char *cmd, char *arg, char *msg)
{
	cmd = ft_strjoin("\033[0;31md-sh: \033[0;0m", cmd);
	if (!cmd)
		return ;
	arg = ft_strjoin(cmd, arg);
	free(cmd);
	if (!arg)
		return ;
	msg = ft_strjoin(arg, msg);
	free(arg);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

void	syntax_err_msg(char *str)
{
	int	i;

	i = 0;
	if (*str == NULL_TERM)
		str = "newline";
	else if (ft_strncmp("||", str, 2) == 0 || ft_strncmp("&&", str, 2) == 0
		|| ft_strncmp(">>", str, 2) == 0 || ft_strncmp("<<", str, 2) == 0)
		i = 2;
	else if (*str == PIPE || *str == )
}
