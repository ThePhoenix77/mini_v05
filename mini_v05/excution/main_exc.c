/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:01:31 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/11 14:55:20 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//

// void print_cmd_args(t_cmd_args *cmd_args)
// {
//     int i=0;
//     while (cmd_args)
//     {
//         printf("Argument %d: %s\n", i, cmd_args->content);
//         cmd_args = cmd_args->next;
//         i++;
//     }
// }
//

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

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    if (pipe(pipe_fd) < 0)
        handle_error("pipe");
    pid1 = fork();
    if (pid1 == 0)
	{
        dupping_and_closing(pipe_fd);
        handle_redirection(list->redir);
        execve(get_path(list->cmd_args->content, global->env),
            get_args_arr(list->cmd_args), global->env);
        exit(1);
    }
	else if (pid1 > 0)
	{
        pid2 = fork();
        if (pid2 == 0)
		{
            dupping_and_closing(pipe_fd);
            handle_redirection(list->next->redir);
            execve(get_path(list->next->cmd_args->content, global->env),
                get_args_arr(list->next->cmd_args), global->env);
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
            path = get_path(list->cmd_args->content, global->env);
            if (!path)
                return cmd_msg(list, global);
            pid = fork();
            if (pid == 0)
			{
                handle_redirection(list->redir);
                execve(path, get_args_arr(list->cmd_args), global->env);
                exit(1);
            }
			else if (pid > 0)
				waitpid(pid, &global->exit_status, 0);
        } else if (list->type == PiPe)
			execute_pipe(list, global);
        list = list->next;
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void cmd_msg(t_exc_list *list, t_global *global)
// {
// 	printf("%s: command not found\n", list->cmd_args->content);
// 	global->exit_status = 127;
// 	return ;
// }

// void closing_and_waiting(t_global *global, pid_t pid1, pid_t pid2, int pipe_fd[2])
// {
//     close(pipe_fd[0]); // Close read end in parent
//     close(pipe_fd[1]); // Close write end in parent
//     waitpid(pid1, &global->exit_status, 0);
//     waitpid(pid2, &global->exit_status, 0);
// }

// void dupping_and_closing(int pipe_fd[2], int is_first_child)
// {
//     if (is_first_child)
//     {
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[0]); // Close read end
//         close(pipe_fd[1]); // Close write end
//     }
//     else
//     {
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[1]); // Close write end
//         close(pipe_fd[0]); // Close read end
//     }
// }

// void execute_pipe(t_exc_list *list, t_global *global)
// {
//     int pipe_fd[2];
//     pid_t pid1, pid2;

//     if (pipe(pipe_fd) < 0)
//         handle_error("pipe");

//     pid1 = fork();
//     if (pid1 == 0) // First child
//     {
//         dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
//         close(pipe_fd[0]); // Close read end
//         close(pipe_fd[1]); // Close write end
//         handle_redirection(list->redir);
//         if (execve(get_path(list->cmd_args->content, global->env),
//                    get_args_arr(list->cmd_args), global->env) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if (pid1 > 0)
//     {
//         pid2 = fork();
//         if (pid2 == 0) // Second child
//         {
//             dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
//             close(pipe_fd[1]); // Close write end
//             close(pipe_fd[0]); // Close read end
//             handle_redirection(list->next->redir);
//             if (execve(get_path(list->next->cmd_args->content, global->env),
//                        get_args_arr(list->next->cmd_args), global->env) == -1)
//             {
//                 perror("execve");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         else if (pid2 > 0)
//         {
//             close(pipe_fd[0]); // Close read end in parent
//             close(pipe_fd[1]); // Close write end in parent
//             closing_and_waiting(global, pid1, pid2, pipe_fd);
//         }
//         else
//             handle_error("fork");
//     }
//     else
//         handle_error("fork");
// }

// void execute_list(t_exc_list *list, t_global *global)
// {
// 	char *path;
// 	pid_t pid;
	
// 	// print_cmd_args(list->cmd_args);
// 	while (list)
// 	{
// 		if (list->type == CMD)
// 		{
// 			path = get_path(list->cmd_args->content, global->env);
// 			if (!path)
// 				return (cmd_msg(list, global));
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				handle_redirection(list->redir);
// 				execve(path, get_args_arr(list->cmd_args), global->env);
// 				exit(1);
// 			}
// 			else if (pid > 0)
// 				waitpid(pid, &global->exit_status, 0);
// 		}
// 		else if (list->type == PiPe)
// 			execute_pipe(list, global);
// 		list = list->next;
// 	}
// }



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
	cmd_or_builtins_chech(global->root, global);
	// execute_list(global->root, global);
	free_lst(&global->pre_head);
	global->pre_head = NULL;
	free_exc_list(&global->root);
}
/*void cmd_msg(t_exc_list *list, t_global *global)
{
    printf("%s: command not found\n", list->cmd_args->content);
    global->exit_status = 127;
}

void dupping_and_closing(int pipe_fd[2], int flag)
{
	//flag kan checki wach first child
    if (flag)
	{
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    } else {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
    }
}

void closing_and_waiting(t_global *global, pid_t pid1, pid_t pid2, int pipe_fd[2])
{
	close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, &global->exit_status, 0);
    waitpid(pid2, &global->exit_status, 0);
}

void execute_pipe(t_exc_list *list, t_global *global)
{
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        handle_error("pipe");
    }

    // Fork the first child
    pid1 = fork();
    if (pid1 < 0) {
        handle_error("fork");
    } else if (pid1 == 0) { // First child process
        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]); // Close the read end of the pipe
        close(pipe_fd[1]); // Close the write end after duplicating

        // Handle any redirection for the first command
        handle_redirection(list->redir);

        // Execute the first command
        char *path = get_path(list->cmd_args->content, global->env);
        if (!path) {
            cmd_msg(list, global);
            exit(EXIT_FAILURE);
        }
        char **args = get_args_arr(list->cmd_args);
        execve(path, args, global->env);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Fork the second child
    pid2 = fork();
    if (pid2 < 0) {
        handle_error("fork");
    } else if (pid2 == 0) { // Second child process
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]); // Close the write end of the pipe
        close(pipe_fd[0]); // Close the read end after duplicating

        // Handle any redirection for the second command
        handle_redirection(list->next->redir);

        // Execute the second command
        char *path = get_path(list->next->cmd_args->content, global->env);
        if (!path) {
            cmd_msg(list->next, global);
            exit(EXIT_FAILURE);
        }
        char **args = get_args_arr(list->next->cmd_args);
        execve(path, args, global->env);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    global->exit_status = WEXITSTATUS(status); // Capture the exit status of the last child
}

void execute_list(t_exc_list *list, t_global *global)
{
	char *path;
	pid_t pid;
	
    while (list)
	{
        if (list->type == CMD)
		{
            path = get_path(list->cmd_args->content, global->env);
            if (!path)
				return (cmd_msg(list, global));
            pid = fork();
            if (pid < 0)
				handle_error("fork");
            else if (pid == 0)
			{
                handle_redirection(list->redir);
                execve(path, get_args_arr(list->cmd_args), global->env);
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
			else 
				waitpid(pid, &global->exit_status, 0);
		}
		else if (list->type == PiPe)
			execute_pipe(list, global);
        list = list->next;
    }
}*/