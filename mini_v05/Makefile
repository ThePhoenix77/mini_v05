CC = cc

CFLAGS =# -Wall -Wextra -Werror

NAME = minishell

READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include

HEADER = includes

CFILES = Utils/linked_list_fun.c Utils/utils.c Utils/Utils_Tokeniz1.c Utils/Utils_Tokeniz2.c\
		 Utils/ft_tokeniz.c Utils/check_syntax.c Utils/clean_memory.c expanding/check_node_expn.c expanding/ft_expand.c\
		 expanding/exp_utils.c expanding/last_step_exp.c expanding/list_exp_fun.c expanding/exp_utils2.c\
		 env/env_utils2.c env/env_utils3.c env/shell_level.c env/env_utils.c Utils/ft_heredoc.c Utils/here_doc_utils.c Utils/check_redir.c\
		 builtins/builtins_utils.c builtins/ft_echo.c builtins/ft_exit.c builtins/ft_pwd.c\
		 builtins/ft_export.c builtins/ft_unset.c builtins/ft_cd.c builtins/ft_env.c\
		 excution/build_exc_list.c excution/main_exc.c excution/exc_utils.c Utils/signals.c excution/exc_list_utils.c\
		 excution/prepare_exc_list.c excution/redir_handle.c excution/path_finder.c excution/exc_utils2.c excution/cmd_list.c excution/redir_list.c main.c 

OFILES = $(CFILES:%.c=%.o)

LIBFT_DIR = libft

RM = rm -rf

CC += -g #-fsanitize=address

all: $(NAME)

$(NAME): $(OFILES)
	make -C $(LIBFT_DIR)
	$(CC) $(OFILES) -L $(LIBFT_DIR) -L $(READLINE_L) -lft -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -I $(HEADER) -I $(READLINE_I) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) -rf $(OFILES)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) -rf $(NAME)

re: fclean all