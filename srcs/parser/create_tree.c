#include "../../includes/minishell.h"

t_bool	get_type(char *str, t_node_info **info);

int create_tree(char *str, t_node **root, int *hd_num, t_minishell *minish)
{
	t_node_info	*info;
	t_bool		status;
	int 		type;

	status = get_type(str, &info);
	if (status == false)
		return (MALLOC_ERR);
	if (create_node(info, root) == false)
		return (MALLOC_ERR);
	type = info->type;
	if (type == T_AND || type == T_OR || type == T_PIPE)
		status = add_or_and_pipe_tree(info, root, hd_num, minish);
	else if (type == T_BRACKET)
		status = add_br(info, root, hd_num, minish);
	else if (type == T_CMD)
		status = add_cmd(info, root, hd_num, minish);
	else if (type == T_CMD_BR)
		status = add_cmd_br(info, root, hd_num, minish);
	free(info);
	if (status != SUCCESS)
	{
		free_tree(root);
		return (status);
	}
	return (SUCCESS);
}

t_bool	get_type(char *str, t_node_info **info)
{
	int status;

	status = lexer(info, str, T_AND, ft_strlen(str) - 1);
	return (status);
}