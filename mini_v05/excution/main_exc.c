/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:01:31 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/13 10:03:30 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool join_nodes(t_global *global, t_lst **node)
{
	char    *save;

	if (((*node)->type == ENV || (*node)->type == WORD)
		&& ((*node)->next && ((*node)->next->type == ENV
		|| (*node)->next->type == WORD)))
	{
		while (*node && ((*node)->type == ENV || (*node)->type == WORD))
		{
			save = ft_strjoin2(global->content, (*node)->content);
			if (!save)
				malloc_failed(global);
			if (global->content)
				free(global->content);
			global->content = save;
			*node = (*node)->next;
		}
		global->type = WORD;
		add_pre_list(global);
		return (SUCCESS);
	}
	return (FAILURE);
}

void    prepere_list(t_global *global)
{
	global->tmp = global->head;
	while (global->tmp)
	{
		if (global->tmp->type == ENV_SPL)
		{
			split_env(global, global->tmp);
			if (join_cont(global, global->tmp) == 3)
				global->tmp = global->tmp->next;
		}
		else if (global->tmp->type != WHITE_SPACE)
		{
			if (join_nodes(global, &global->tmp) == SUCCESS)
				continue ;
			global->content = ft_strdup(global->tmp->content);
			if (global->type == ENV)
				global->type = WORD;
			global->type = global->tmp->type;
			global->state = global->tmp->state;
			add_pre_list(global);
		}
		global->tmp = global->tmp->next;
	}
}

void cmd_msg(t_exc_list *list, t_global *global)
{
	printf("%s: command not found\n", list->cmd_args->content);
	global->exit_status = 127;
	return ;
}

void dupping_and_closing(int pipe_fd[2])
{
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

void closing_and_waiting(t_global* global, pid_t pid1, pid_t pid2, int pipe_fd[2])
{
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, &global->exit_status, 0);
    waitpid(pid2, &global->exit_status, 0);
}

void execute_pipe(t_exc_list* list, t_global* global)
{
    int pipe_fd[2];
    pid_t pid1;
    pid_t pid2;
    char *path;
    
    path = get_path(list->cmd_args->content, global);
    if (!path)
        return (cmd_msg(list, global));
    // printf("----------PATH : %s\n", path);

    if (pipe(pipe_fd) < 0)
        handle_error("pipe");
    pid1 = fork();
    if (pid1 == 0)
	{
        dupping_and_closing(pipe_fd);
        handle_redirection(list->redir);
        if (execve(path, get_args_arr(list->cmd_args), global->env) == -1)
        {
            perror("execve");
            // exit(EXIT_FAILURE);
        }
        exit(1);
    }
	else if (pid1 > 0)
	{
        pid2 = fork();
        path = get_path(list->next->cmd_args->content, global);
        if (!path)
            return (cmd_msg(list, global));
        if (pid2 == 0)
		{
            dupping_and_closing(pipe_fd);
            handle_redirection(list->next->redir);
            if (execve(path, get_args_arr(list->next->cmd_args), global->env) == -1)
            {
                perror("execve");
                // exit(EXIT_FAILURE);
            }
            exit(1);
        }
		else if (pid2 > 0)
			closing_and_waiting(global, pid1, pid2, pipe_fd);
        else
            handle_error("fork");
    }
	else
        handle_error("fork");
}

void execute_list(t_exc_list* list, t_global* global)
{
    char* path;
    pid_t pid;

    while (list)
	{
        if (list->type == CMD)
		{
            path = get_path(list->cmd_args->content, global);
            if (!path)
                return (cmd_msg(list, global));
            // printf("-------------Path is : %s\n", path);
            if (!path)
                return cmd_msg(list, global);
            pid = fork();
            if (pid == 0)
			{
                handle_redirection(list->redir);
                if (execve(path, get_args_arr(list->cmd_args), global->env) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
                exit(1);
            }
			else if (pid > 0)
				waitpid(pid, &global->exit_status, 0);
        } else if (list->type == PiPe)
			execute_pipe(list, global);
        list = list->next;
    }
}

void cmd_or_builtins_chech(t_exc_list *list, t_global *global)
{
	char *content;

	content = list->cmd_args->content;
	if (ft_strcmp(content, "echo") == 0)
        ft_echo(list->cmd_args);
    else if (ft_strcmp(content, "cd") == 0)
        ft_cd(global, list->cmd_args);
    else if (ft_strcmp(content, "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(content, "export") == 0)
        ft_export(global, list->cmd_args);
    else if (ft_strcmp(content, "unset") == 0)
        ft_unset(global, list->cmd_args);
    else if (ft_strcmp(content, "env") == 0)
        ft_env(global);
    else if (ft_strcmp(content, "exit") == 0)
        ft_exit(global, list->cmd_args);
	else
		execute_list(list, global);
}

void    main_exc(t_global *global)
{
	t_lst   *tmp;

	global->pre_head = NULL;
	prepere_list(global);
	tmp = global->pre_head;
	bulid_list_exc(global);
	env_list_2d_array(global);
    cmd_or_builtins_chech(global->root, global);
    free_lst(&global->pre_head);
	global->pre_head = NULL;
	free_exc_list(&global->root);
}
