# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quvan-de <quvan-de@student.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 15:48:37 by quvan-de          #+#    #+#              #
#    Updated: 2024/09/25 19:42:52 by quvan-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME = minishell
INCLUDES = includes
OBJS_DIR = objs
LIBFT = libft
LIBFT_LIB = $(LIBFT)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I $(INCLUDES) -I $(LIBFT)/includes
RM = rm -rf

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Source files
BUILTINS_DIR = builtins/
BUILTINS = b_utils.c builtins.c cd/cd.c cd/cd_util.c echo.c env.c exit.c export/export.c export/export_add.c \
            export/export_edit.c export/export_other.c export/export_utils.c pwd.c unset.c

DOLLAR_DIR = dollar_expansion/
DOLLAR = exp_dollar_sign.c exp_dollar_sign_utils.c generic_exp_dollar_sign.c q_mark_exp_dollar_sign.c

LEXER_DIR = lexer/
LEXER = cmd_blocks.c common_utils.c lexer.c quote_check.c searchers.c token_blocks.c tokenise.c u_tokenise.c

MINISH_DIR = minishell/
MINISH = free_minish.c init_minish.c main.c run_minish.c

PARSER_DIR = parser/
PARSER = add_nodes.c create_node.c create_tree.c free_tree.c init_constructor.c init_constructor1.c

REDIR_DIR = redirections/
REDIR = append.c check_redir.c heredoc.c prep_heredoc.c prep_redirects.c redir_in.c redir_out.c redirects.c

SIGNALS_DIR = signals/
SIGNALS = interceptor.c toggler.c

SYNVAL_DIR = syntax_validators/
SYNVAL = and_or_val.c cmd_val.c empty_string.c input_val.c pipe_val.c redir_val.c simple_cmd_val.c word_val.c

TRAVTREE_DIR = traverse_tree/
TRAVTREE = bracket_traverser.c cmd_br_traverser.c find_cmd.c is_builtin.c pipe_traverser.c wait_childs.c \
            builtin_runner.c cmd_traverser.c find_exe.c parse_cmd.c tree_traverser.c

UTILS_DIR = utils/
UTILS = add_hst.c init_hst.c init_shlvl.c realloc.c save_hst_file.c split_before_wc.c update_prompt.c \
         ctl_d_handler.c init_pwd.c print_errors.c remove_quotes.c sort_str_arr.c split_with_quotes.c

WC_DIR = wildcards/
WC = wc.c wc_check_asterix.c wc_exp_entities.c wc_fill_arr_entities.c wc_main.c wc_main_utils.c wc_sort.c wc_utils.c

# Collect all source files
SRC_FILES += $(addprefix $(BUILTINS_DIR), $(BUILTINS))
SRC_FILES += $(addprefix $(DOLLAR_DIR), $(DOLLAR))
SRC_FILES += $(addprefix $(LEXER_DIR), $(LEXER))
SRC_FILES += $(addprefix $(MINISH_DIR), $(MINISH))
SRC_FILES += $(addprefix $(PARSER_DIR), $(PARSER))
SRC_FILES += $(addprefix $(REDIR_DIR), $(REDIR))
SRC_FILES += $(addprefix $(SIGNALS_DIR), $(SIGNALS))
SRC_FILES += $(addprefix $(SYNVAL_DIR), $(SYNVAL))
SRC_FILES += $(addprefix $(TRAVTREE_DIR), $(TRAVTREE))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS))
SRC_FILES += $(addprefix $(WC_DIR), $(WC))

SRCS = $(addprefix ./srcs/, $(SRC_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

# Phony targets to avoid name conflicts
.PHONY: all clean fclean re lib tmp

# Compilation steps
all: lib tmp $(NAME)

lib: $(LIBFT_LIB)

$(LIBFT_LIB):
	@echo "$(GREEN)Building libft...$(BLUE)"
	@$(MAKE) -C $(LIBFT)

tmp:
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "$(YELLOW)Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -L $(LIBFT) -lft -o $@ $^ -lm -lreadline
	@echo "$(GREEN)$(NAME) compiled successfully!$(DEF_COLOR)"

# Pattern rule for object files
$(OBJS_DIR)/%.o: ./srcs/%.c | tmp
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling: $< -> $@$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Object file created: $(WHITE)$(notdir $@)$(RED)[Done]$(DEF_COLOR)"

# Clean targets
clean:
	@echo "$(RED)Cleaning object files...$(DEF_COLOR)"
	@$(MAKE) clean -C $(LIBFT)
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Objects cleaned$(DEF_COLOR)"

fclean: clean
	@echo "$(RED)Cleaning everything, including executable...$(DEF_COLOR)"
	@$(MAKE) fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(RED)Everything cleaned$(DEF_COLOR)"

re: fclean all
