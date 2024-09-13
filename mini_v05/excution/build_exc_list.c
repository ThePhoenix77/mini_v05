/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exc_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:51:54 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/06 15:24:27 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_redir(t_redir *redir)
{
    while (redir)
    {
        printf("Redirection File: %s\n", redir->file_name);
        printf("File Type: %d\n", redir->file_type);
        printf("Type: %d\n", redir->type);
        redir = redir->next;
    }
}

void print_cmd_args(t_cmd_args *cmd_args)
{
    while (cmd_args)
    {
        printf("  *  %s\n", cmd_args->content);
        cmd_args = cmd_args->next;
    }
}

void print_exc_list(t_exc_list *list)
{
    while (list)
    {
        // Print the redirection list
        printf("Redirections:\n");
        if (list->redir)
            print_redir(list->redir);
        else
            printf("No redirections\n");
        printf("\n--------------------------------\n");
        // Print the command arguments
        printf("Command Arguments:\n");
        if (list->cmd_args)
            print_cmd_args(list->cmd_args);
        else
            printf("No command arguments\n");
        printf("\n--------------------------------\n");
        // Print the node type
        printf("Node Type: %d\n", list->type);
        printf("\n--------------------------------\n");
        // Print the file descriptors (fd)
        printf("FD In: %d, FD Out: %d\n", list->fd.in, list->fd.out);
        printf("\n--------------------------------\n");

        // Move to the next element in the list
        list = list->next;
    }
}
/*cat Makefile | wc -l > tttt*/

void    bulid_list_exc(t_global *global)
{
    t_lst       *mv_node;
    t_lst       *save;
    t_exc_list  *new;

    mv_node = global->pre_head;
    save = global->pre_head;
    while (mv_node)
    {
        if (mv_node->type == PIPE)
        {
            new = new_exc_spot(global, PiPe);
            add_back_exc(&global->root, new);
            mv_node = mv_node->next;
            // printf("Encountered PIPE\n");
        }
        create_node(global, &mv_node);
    }
}
