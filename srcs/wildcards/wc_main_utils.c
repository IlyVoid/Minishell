/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_main_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:55:46 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:07:00 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	if_only_asterix(char *pattern)
{
	while (*pattern)
	{
		if (*pattern++ != '*')
			return (false);
	}
	return (true);
}

static void	quote_checker(char *str, int *i, int *wc_flag)
{
	if (str[*i] == S_QUOTE && *wc_flag == 0)
		*wc_flag = 1;
	else if (str[*i] == D_QUOTE && *wc_flag == 0)
		*wc_flag = 2;
	else if ((str[*i] == S_QUOTE && *wc_flag == 1) || (str[*i] == D_QUOTE
			&& *wc_flag == 2))
		*wc_flag = 0;
}

void	trans_str(char *line, char *pattern)
{
	int	wc_flag;
	int	i;

	wc_flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ASTERIX)
			line[i] = SEPERATOR;
		i++;
	}
	i = 0;
	while (pattern[i])
	{
		quote_checker(pattern, &i, &wc_flag);
		if (wc_flag == 1 || wc_flag == 2)
		{
			if (pattern[i] == ASTERIX)
				pattern[i] = SEPERATOR;
		}
		i++;
	}
}

t_bool	trans_str_back(char *line, char *pattern, t_bool res)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SEPERATOR)
			line[i] = ASTERIX;
		i++;
	}
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == SEPERATOR)
			pattern[i] = ASTERIX;
		i++;
	}
	return (res);
}

int	arr_len_entities(int sub_arr_len)
{
	DIR			*dir;
	t_dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("\033[0;31md-sh: \033[0;0m opendir() error in wildcards");
		return (SYS_ERROR);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		sub_arr_len++;
		entry = readdir(dir);
	}
	if (closedir(dir) == SYS_ERROR)
	{
		perror("\033[0;31md-sh: \033[0;0m closedir() error in wildcards");
		return (SYS_ERROR);
	}
	if (entry == NULL)
		return (sub_arr_len);
	return (SYS_ERROR);
}
