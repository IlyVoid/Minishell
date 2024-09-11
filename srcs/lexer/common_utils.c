#include "../../includes/minishell.h"

t_bool	is_odd(int n)
{
	return (n % 2);
}

int check_round_br(char *str, int point)
{
	int i;
	int key;
	int type_of_quote;

	i = (int)ft_strlen(str) - 1;
	key = 0;
	type_of_quote = 0;
	while (i >= point)
	{
		check_inside_quote(str, &i, &type_of_quote);
		if (!type_of_quote)
		{
			if (str[i] == O_ROUND)
				key++;
			if (str[i] == C_ROUND)
				key--;
			i--;
		}
		else
			i--;
	}
	return (!key);
}

int	check_quote(char *str, int point, int symbol)
{
	int i;
	int pair[2];

	i = (int) ft_strlen(str) - 1;
	pair[0] = 0;
	pair[1] = 0;
	while (i >= point)
	{
		if (str[i] == symbol)
			pair[0]++;
		i--;
	}
	while (--point > 0)
		if (str[point] == symbol)
			pair[1]++;
	return (is_odd(pair[0]) == false && is_odd(pair[1]) == false);
}

int first_char_is_br_space_excluded(char *str)
{
	int i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		while (str[i] == SPCE)
			i++;
		if (str[i] == O_ROUND)
			return (1);
		else
			return (0);
	}
	return (0);
}