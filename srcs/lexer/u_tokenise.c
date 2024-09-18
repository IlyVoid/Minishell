/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:43:40 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/18 13:58:21 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*part_cmd(char *str, int *i, int type_of_quote)
{
	while (str[*i] != NULL_TERM)
	{
		check_inside_quotes(str, i, &type_of_quote);
		if (!type_of_quote)
		{
			if (str[*i] == O_ROUND)
			{
				while (str[*i] != C_ROUND)
					(*i)++;
				if (str[*i] == C_ROUND)
				{
					str[(*i)++] = NULL_TERM;
					return (str);
				}
			}
			(*i)++;
		}
		else
			(*i)++;
	}
	return (NULL);
}

static void	mod_util_str(char *str, char *redir, int *i, int *j)
{
	redir[*j] = str[*i];
	str[*i] = SPCE;
	(*j)++;
	(*i)++;
}

static void	redir_fill(char *str, char **redir, int *i, int *j)
{
	int	q_flag;

	q_flag = 0;
	while ((str[*i] == REDIR_L || str[*i] == REDIR_R || str[*i] == SPCE
			|| str[*i] == HT) && str[*i] != NULL_TERM)
		mod_util_str(str, *redir, i, j);
	while (str[*i] != NULL_TERM)
	{
		if ((str[*i] == S_QUOTE || str[*i] == D_QUOTE) && q_flag == 0)
			q_flag = str[*i];
		else if (str[*i] == S_QUOTE && q_flag == S_QUOTE)
			q_flag = 0;
		else if (str[*i] == D_QUOTE && q_flag == D_QUOTE)
			q_flag = 0;
		if (q_flag == 0 && (str[*i] == SPCE || str[*i] == REDIR_L
				|| str[*i] == REDIR_R || str[*i] == HT || str[*i] == NULL_TERM))
			break ;
		else
			mod_util_str(str, *redir, i, j);
	}
	(*redir)[(*j)++] = SEPERATOR;
	(*i)--;
}

int	mod_cmd_str_no_br(char *str, char **redir, int i, int j)
{
	int	q_flag;

	q_flag = 0;
	if (!str)
		return (-1);
	*redir = (char *)ft_calloc(ft_strlen(str) * 2, sizeof(char));
	if (!*redir)
		return (-1);
	while (str[i] != NULL_TERM)
	{
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE) && q_flag == 0)
			q_flag = str[i];
		else if (str[i] == S_QUOTE && q_flag == S_QUOTE)
			q_flag = 0;
		else if (str[i] == D_QUOTE && q_flag == D_QUOTE)
			q_flag = 0;
		if (q_flag == 0 && (str[i] == REDIR_L || str[i] == REDIR_R))
			redir_fill(str, redir, &i, &j);
		if (str[i] == NULL_TERM)
			break ;
		i++;
	}
	return (1);
}
