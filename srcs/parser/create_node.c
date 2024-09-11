#include "../../includes/minishell.h"

t_bool	create_node(t_node_info *info, t_node **root)
{
	t_node	*node;

	node = NULL;
	if (info->type == T_AND)
		node = (t_node *)init_t_and();
	else if (info->type == T_OR)
		node = (t_node *)init_t_or();
	else if (info->type == T_PIPE)
		node = (t_node *)init_t_pipe();
	else if (info->type == T_BRACKET)
		node = (t_node *)init_t_br();
	else if (info->type == T_CMD)
		node = (t_node *)init_t_cmd();
	else if (info->type == T_CMD_BR)
		node = (t_node *)init_t_cmd_br();
	if (node == NULL)
	{
		free(info);
		return (false);
	}
	*root = node;
	return (true);
}