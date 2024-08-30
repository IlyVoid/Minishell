/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:36:32 by quvan-de          #+#    #+#             */
/*   Updated: 2024/08/30 14:36:55 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int parse_cmd(char *cmd, char ***res, t_minishell *minish)
{
	char	**arr;
	int 	i;
	int 	status;

	if (string_is_empty(cmd))
		cmd = "";
	arr = wrapper_split_quotes(cmd);
	if (!arr)
		return (MALLOC_ERR);
	i = 0;
	status = 0;
	while (arr[i] && status == 0)
		status = exp_dollar_sign(&arr[i++], minish->env, minish->exit_status);
	if (status == 0)
		status = array_build_wc(&arr, -1, -1, -1);
	if (status != 0 && arr != NULL)
		ft_free_2d_array(arr);
	if (status == 0)
	{
		remove_quotes_arr(arr, 0);
		*res = arr;
	}
	return (status);
}
