/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brsantsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:28:37 by brsantsc          #+#    #+#             */
/*   Updated: 2024/09/26 23:15:38 by quvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_prompt(void)
{
	char	*prompt;
	char	*pwd;
	int		i;

	i = 0;
	prompt = NULL;
	pwd = getcwd(NULL, 0);
	while (pwd[i] != '\0')
		i++;
	while (pwd[i] != '/')
		i--;
	prompt = ft_strdup("\033[92m✓\033[0m");
	prompt = ft_strjoin(prompt, pwd + i,
			ft_strlen(pwd + i) + ft_strlen(prompt) + 1);
	prompt = ft_strjoin(prompt, " $ ", ft_strlen(prompt) + 4);
	free(pwd);
	return (prompt);
}

void	set_and_execute(char *input, t_data	*g_data)
{
	int			ret;
	char		**splitted_input;

	if (!ft_cntrl(input))
		return ;
	if (!ft_quote_check(input))
		return ;
	splitted_input = ft_parser(input, 0);
	if (splitted_input == NULL)
	{
		free_matrix(splitted_input);
		return ;
	}
	g_data->exp = ft_expander(splitted_input, 0, 0, g_data);
	free_matrix(splitted_input);
	g_data->exp = subsplit(g_data->exp);
	ret = check_strange_chars(g_data->exp);
	if (ret != 0)
	{
		free_exp(g_data->exp);
		ft_error(ret, 0);
		return ;
	}
	ft_fill_block(g_data->exp, g_data);
	ft_ft_ft(g_data);
}

void	ft_start_proccess(t_data	*g_data)
{
	char	*input;

	while (1)
	{
		ft_signal(1, g_data);
		g_data->default_prompt = ft_prompt();
		input = readline(g_data->default_prompt);
		if (!input)
		{
			free_string(g_data->default_prompt);
			free_string(input);
			ft_signal(3, g_data);
		}
		else if (input && *input && g_data->default_prompt)
		{
			set_and_execute(input, g_data);
			add_history(input);
		}
		free_string(g_data->default_prompt);
		free_string(input);
	}
}

char	**ft_copy_matrix(char **matrix)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		if (!new_matrix[i])
			return (NULL);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*g_data;

	g_data = NULL;
	if (argc != 1 || argv[1])
		ft_exit("! Too many arguments.\n", 0, g_data);
	g_data = malloc(sizeof(t_data));
	if (!g_data)
		return (-1);
	g_data->environmental = NULL;
	g_data->env = ft_copy_matrix(env);
	g_data->exit_status = 0;
	ft_fill_env(env, g_data);
	ft_start_proccess(g_data);
	return (0);
}
