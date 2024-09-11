#include "../../includes/minishell.h"

int cmd_block(t_node_info **node, char *str, int type)
{
	if (redir_search(str))
		return (set_node_info_cmd(node, str, type));
	else
		return (set_node_simple_cmd(node, str, T_CMD));
	return (0);
}

int cmd_br_block(t_node_info **node, char *str, int type)
{
	if (search_br(str))
		return (set_node_info_cmd_br(node, str, type));
	return (0);
}