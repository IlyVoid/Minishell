/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:04:46 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/25 15:10:09 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_pattern_match(char **line, char **pattern,
	t_bool *wildcard, char **placeholder)
{
	if (**pattern == **line)
	{
		(*line)++;
		(*pattern)++;
		return (0);
	}
	else if (**pattern == ASTERIX)
	{
		if (*(++(*pattern)) == NULL_TERM)
			return (1);
		*placeholder = *pattern;
		*wildcard = true;
		return (0);
	}
	else if (*wildcard)
	{
		if (*pattern == *placeholder)
			(*line)++;
		else
			*pattern = *placeholder;
		return (0);
	}
	else
		return (-1);
}

t_bool	wc_strcmp(char *line, char *pattern)
{
	int		status;
	char	*placeholder;
	t_bool	wildcard;
	char	*line_copy;
	char	*pattern_copy;

	status = 0;
	placeholder = NULL;
	wildcard = false;
	trans_str(line, pattern);
	line_copy = line;
	pattern_copy = pattern;
	while (*line)
	{
		status = process_pattern_match(&line, &pattern, &wildcard,
				&placeholder);
		if (status == 1)
			return (trans_str_back(line_copy, pattern_copy, true));
		else if (status == -1)
			return (trans_str_back(line_copy, pattern_copy, false));
	}
	if (*pattern == NULL_TERM || if_only_asterix(pattern))
		return (trans_str_back(line_copy, pattern_copy, true));
	else
		return (trans_str_back(line_copy, pattern_copy, false));
}
