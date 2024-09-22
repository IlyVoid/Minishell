/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:37:22 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 15:24:26 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	zero_check(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != NULL_TERM)
		return (true);
	return (false);
}

static void	exit_count_of_arg_err(t_minishell *minish)
{
	if (minish->is_parent == true)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	print_err_msg("exit: ", "too many arguments\n");
	minish->exit_status = GENERIC_ERROR;
}

static void	exit_nbr_format_arg_err(t_minishell *minish, char *str)
{
	if (minish->is_parent == true)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	arg_err_msg("exit: ", str, ": numeric argument required\n");
	minish->exit_status = UNEXPECTED_EXIT;
	if (minish->is_parent == true)
		end_process(minish);
	exit(minish->exit_status);
}

void	run_exit(char **arr, t_minishell *minish, long nbr)
{
	if (ft_arrlen((void **)arr) > 1)
	{
		nbr = ft_atol(arr[0]);
		if ((zero_check(arr[0]) && nbr == 0) || check_non_digit(arr[0]))
			exit_nbr_format_arg_err(minish, arr[0]);
		else
			exit_count_of_arg_err(minish);
		return ;
	}
	else if (!*arr)
		minish->exit_status = SUCCESS;
	else
	{
		nbr = ft_atol(arr[0]);
		if ((zero_check(arr[0]) && nbr == 0) || check_non_digit(arr[0]))
			exit_nbr_format_arg_err(minish, arr[0]);
		else
			minish->exit_status = (unsigned char)nbr;
	}
	if (minish->is_parent == true)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (minish->is_parent == true)
		end_process(minish);
	exit(minish->exit_status);
}

void	end_process(t_minishell *minish)
{
	int	status;

	rl_clear_history();
	save_hst_file(minish);
	status = minish->exit_status;
	ft_free_minish(minish);
	exit(status);
}
