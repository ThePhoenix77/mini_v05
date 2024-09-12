/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:57:29 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/12 22:41:15 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

# define SUCCESS true
# define FAILURE false
# define HISTORY_FILE "~/.bash_history"
# define META_CHARS " \t\n\'\"><|"

/*~~~~~~~~~~~Syntax Error~~~~~~~~~~~~*/
# define UNCLOSED_QUOTE "minishell: syntax error: unexpected end of file.\n"
# define ERROR "minishell: syntax error near unexpected token `"
# define ERR_MANY_HERDOCS "minishell-1.0$: maximum here-document count exceeded\n"
/*~~~~~~~~~~~~~Excution Errors~~~~~~~~~~*/
# define ERR_CMD_NF ": command not found\n"

#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "structs.h"
// #include "../builtins/builtins.h"

/*~~~~~~~~~~~~~~~~~~~~~signals~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void init_sigaction();
void signals_handler(int sig);
/*----------------linked list functions--------------*/
bool			add_back(t_lst **head, t_lst  **new);
void			add_list(t_global *global);
void			free_lst(t_lst	**head);
t_lst			*last_node(t_lst *head);
t_lst			*new_node(t_global *global);
/*----------------linked env list functions--------------*/
void			add_env_back(t_env_list **head, t_env_list *new);
void			free_env_list(t_env_list **head);
t_env_list		*last_env_node(t_env_list *head);
t_env_list		*new_env_node(char   *content);
/*------------------Env functions-----------------------*/
bool			update_env(t_env_list **env, char *new_val);
t_env_list		*get_var_env(t_global *global, char  *var);
bool			shell_level(t_global *global);
bool			empty_env(t_global *global);
/*----------------utils functions-----------------------*/
void			init_global(t_global *global, char **env);
int				ft_strlen_un_del(char *sep, char *str);
int				ft_strlen_un_char(char *str, char c);
int				check_valid_in(t_global *global);
void			free_memory(t_global *global);
int             ft_strcmp(char *s1, char *s2);
/*~~~~~~~~~~~~~~Tonkenzition functions~~~~~~~~~~~~~~~~*/
void			update_line(char **line, int len_skip, t_global *global);
char			*get_word(char **line, int len, t_global *global);
void			get_str_inside_quote(t_global *global);
void			skip_ec_t(t_global *global, int flag); //skip spaces and tabs and new line.
bool			check_heredoc_dred(t_global *global);
bool            check_num_heredoc(t_global *global);
bool			check_operator(t_global *global);
void            check_here_doc(t_global *global);
bool			check_syntax(t_global *global);
void			check_state(t_global *global); //check state is it inside Double or single quote.
void			check_type(t_global *global);
void			ft_tokeniz(t_global *global);
void			get_opr(t_global *global);
/*~~~~~~~~~~~~~~~~~~~~Expanding~~~~~~~~~~~~~~~~~~~~*/
bool    		add_exp_back(t_expand_list **head, t_expand_list *new);
bool			special_expand(t_global *global, t_lst **node);
void			last_step_exp(t_global *global, t_lst *node);
char			*ft_strjoin2(char const *s1, char const *s2);
bool			get_exp_var(t_global *global, char **line);
void			finish_exp(t_global *global, t_lst **node);
bool			split_exp(t_global *global, char **line);
t_expand_list   *last_exp_node(t_expand_list   *head);
void			free_exp_list(t_expand_list   **head);
void			update_var_name(t_global *global);
void			transform_env(t_global *global);
bool			check_expand(t_global *global);
bool			main_exp_fun(t_global *globol);
void			join_result(t_global *global);
t_expand_list   *new_exp_node(char *content);
/*~~~~~~~~~~~~~~~~~~~~~here_doc~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool    check_heredoc(t_global *global);
void	open_heredoc_file(t_global *global);
void    empty_here_doc(t_global *global, t_lst *node);
/*~~~~~~~~~~~~~~~~~~~~~excution~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void        split_env(t_global *global, t_lst *tmp);
int         join_cont(t_global *global, t_lst *tmp);
void        add_pre_list(t_global *global);
void        main_exc(t_global *global);
void        add_back_exc(t_exc_list **head, t_exc_list *new);
t_exc_list  *new_exc_spot(t_global *global, t_type_node type);
t_exc_list  *last_exc_node(t_exc_list *head);
void        bulid_list_exc(t_global *global);
void        free_exc_list(t_exc_list **head);
void    create_node(t_global *global, t_lst **node);

//
char *find_path(char **split, char *cmd);
char *get_path(char *cmd, char **envp);
void handle_redir_out(t_redir *redir);
void handle_redir_in(t_redir *redir);
void handle_dredir_out(t_redir *redir);
void handle_redirection(t_redir *redir_list);
char **get_args_arr(t_cmd_args *cmd_args);
void handle_error(char *msg);

/*~~~~~~~~~~~~~~~~~~~~~~Command Args~~~~~~~~~~~~~~~~~~~~*/
size_t      ft_strnlen(char *s, size_t maxlen);
char        *ft_strncpy(char *dest, char *src, size_t n);
char        *ft_strndup(char *s, size_t n);
t_env_list  *find_var(t_env_list *env_list, char *key);
char        *create_new_content(char *key, char *value);
void        update_env_var(t_env_list *env_var, char *new_content);
// void        add_or_update_env_var(t_global *global, char *key, char *value);
void        add_or_update_env_var(t_global *global, char *key, char *value, int type);
t_env_list  *get_var_env2(t_global *global, char *var);
void        ft_cd(t_global *global, t_cmd_args *cmd_args);
void        ft_echo(t_cmd_args *cmd_args);
int        ft_pwd();
void        ft_env(t_global *global);
void        ft_exit(t_global *global, t_cmd_args *cmd_args);
void        ft_export(t_global *global, t_cmd_args *cmd_args);
void        ft_unset(t_global *global, t_cmd_args *cmd_args);
void chech_builtins(t_exc_list *list, t_global *global);

//
/*~~~~~~~~~~~~~~~~~~~~~~Command Args~~~~~~~~~~~~~~~~~~~~*/
t_cmd_args  *new_cmd_element(t_global *global, char *content);
void        add_back_element(t_cmd_args **head, t_cmd_args *new);
void        store_cmd_args(t_global *global, t_lst **node);
// void        free_cmd_list(t_cmd_args **head);
/*~~~~~~~~~~~~~~~~~~~~~~redirection lils~~~~~~~~~~~~~~~~~*/
t_redir *new_vertex(t_global *global, t_lst *node);
void    add_back_redir(t_redir **head, t_redir *new);
void    build_redir_list(t_global *global, t_lst **node);


void    check_redir(t_global *global);
void	get_line(t_global *global);
bool	start(t_global *global);
bool    check_env(t_global *global);
void    malloc_failed(t_global *global);
void 	free_2d_array(char **leaks);
#endif