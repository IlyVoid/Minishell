/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:57:26 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/22 14:33:51 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_pwd(char **arr, t_minishell *minish)
{
	char	*curr_dir;
	int		len;

	len = ft_arrlen((void **)arr);
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		arg_err_msg("pwd: `", arr[0], "': options are not supported\n");
		minish->exit_status = CMD_ARG_ERROR;
		return ;
	}
	curr_dir = get_cwd(NULL, 0);
	if (!curr_dir)
	{
		minish->exit_status = GETCWD_ERROR;
		return ;
	}
	printf("%s\n", curr_dir);
	free(curr_dir);
}
