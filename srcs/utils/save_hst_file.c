/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_hst_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:21:48 by quvan-de          #+#    #+#             */
/*   Updated: 2024/09/24 01:35:22 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_write(void *str);

void	save_hst_file(t_minishell *minish)
{
	int	fd;

	if (minish->history_path == NULL)
		return ;
	if (access(minish->history_path, F_OK) != 0)
		printf("creating history file :%s\n", minish->history_path);
	fd = open(minish->history_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror_err_msg("can't write to history file: ", minish->history_path);
		return ;
	}
	close(fd);
	ft_lstiter(minish->history, lst_write);
}

void	lst_write(void *str)
{
	printf("%s\n", (char *)str);
}
