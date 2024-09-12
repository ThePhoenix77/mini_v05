/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:49:33 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/12 10:20:12 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_memory(t_global *global)
{
    if (global->head != NULL)
        free_lst(&global->head);
    if (global->line_input != NULL)
        free(global->line_input);
    if (global->exp_head != NULL)
        free_exp_list(&global->exp_head);
    if (global->pre_head != NULL)
        free_lst(&global->pre_head);
}

void free_2d_array(char **leaks)
{
    int i;

    if (leaks == NULL)
        return;
    i = 0;
    while (leaks[i])
        i++;
    while (i--)
        free(leaks[i]);
    free(leaks);
    leaks = NULL;
    // printf("finish free\n");
}

void malloc_failed(t_global *global)
{
    free_memory(global);
    if (global->content != NULL)
        free(global->content);
    if (global->env_list)
        free_env_list(&global->env_list);
    exit(1);
}

void free_cmd_list(t_cmd_args **head)
{
    t_cmd_args *tmp;

    while (*head)
    {
        tmp = *head;
        (*head) = (*head)->next;
        if (tmp->content)
            free(tmp->content);
        free(tmp);
    }
}

void free_redir_list(t_redir **head)
{
    t_redir *tmp;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        if (tmp->file_name)
            free(tmp->file_name);
        free(tmp);
    }
}

void free_exc_list(t_exc_list **head)
{
    t_exc_list *tmp;

    while (*head)
    {
        tmp = (*head);
        *head = (*head)->next;
        free_cmd_list(&tmp->cmd_args);
        free_redir_list(&tmp->redir);
        free(tmp);
    }
}
