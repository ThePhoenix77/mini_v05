/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:37:25 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/13 15:39:43 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create new node of redirection list
t_redir *new_vertex(t_global *global, t_lst *node)
{
    t_redir *new;
    
    new = (t_redir *)malloc(sizeof(t_redir));
    if (!new)
        malloc_failed(global);
    new->file_name = ft_strdup(node->next->content);
    if (!new->file_name)
    {
        free(new);
        malloc_failed(global);
    }
    if (node->next->type == ERROR_DIS)
        new->type = ERROR_DIS;
    else
        new->type = node->type;
    new->next = NULL;
    return (new);
}
// add back 
void    add_back_redir(t_redir **head, t_redir *new)
{
    t_redir *last;
    
    last =  *head;
    if ((!*head) && !new)
        return ;
    if (!(*head))
        *head = new;
    else
    {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

// create list of redirection
void    build_redir_list(t_global *global, t_lst **node)
{
    t_redir     *new;
    t_exc_list  *last;

    last = last_exc_node(global->root);
    new = (t_redir *)malloc(sizeof(t_redir));
    if (!new)
        malloc_failed(global);
    new->next = NULL;
    new->type = (*node)->type;
    add_back_redir(&last->redir, new);
    (*node) = (*node)->next;
    new->file_name = ft_strdup((*node)->content);
    if (!new->file_name)
        malloc_failed(global);
    (*node) = (*node)->next;
}
