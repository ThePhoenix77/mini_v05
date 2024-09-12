/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:10:58 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/10 22:34:20 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void f(){system ("leaks minishell");}

void	get_line(t_global *global)
{
	read_history(HISTORY_FILE);
	while (1)
	{
		global->line_input = readline("minishell-1.0$ ");
		if (check_valid_in(global) == SUCCESS)
			continue;
		if (check_valid_in(global) == FAILURE)
		{	
			free_memory(global);
			if (global->env_list)
				free_env_list(&global->env_list);
			write(1, "\x1B[Fminishell-1.0$ exit\n", 24);
			break ;
		}	
		add_history(global->line_input);
		skip_ec_t(global, 0);
		if (check_valid_in(global) == SUCCESS)
			continue;
		if (start(global) == FAILURE)
			continue;
		free_memory(global);
	}
	write_history(HISTORY_FILE);
}

bool	start(t_global *global)
{
	t_lst	*tmp;
	t_expand_list *test;
	
	global->type = WORD;
	global->state = GENERAL;
	ft_tokeniz(global);
	if (check_syntax(global) == FAILURE)
	{
		free_memory(global);
		return (FAILURE);
	}
	if (check_num_heredoc(global) == FAILURE)
	{
		ft_putstr_fd(ERR_MANY_HERDOCS, 2);
		free_memory(global);
		exit(2);
	}
	if (check_heredoc(global) == FAILURE)
		return (free_memory(global), FAILURE);
	if (check_expand(global) == FAILURE)
		return (free_memory(global), FAILURE);
	main_exp_fun(global);
	check_redir(global);
	open_heredoc_file(global);
	test = global->exp_head;
	tmp = global->head;
	// while (tmp)
	// {
	// 	printf("Token : [%s]\n",tmp->content);
	// 	printf("Type : [%d]\n",tmp->type);
	// 	printf("Status : [%d]\n",tmp->state);
	// 	tmp = tmp->next;
	// }
	main_exc(global);
	return (SUCCESS);
}


int main(int arc, char **arv, char **env)
{
	t_global	global;
	// atexit(f);
	init_sigaction();
	init_global(&global, env); 
	if (check_env(&global) == FAILURE)
		malloc_failed(&global);
	rl_catch_signals = 0;
	get_line(&global);
	clear_history();
}
