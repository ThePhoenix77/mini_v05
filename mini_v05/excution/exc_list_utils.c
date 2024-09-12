/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:49:25 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/10 10:29:49 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create t_exc_list
// t_exc_list *create_list_node(t_type_node type)
// {
//     t_exc_list *root;
    
//     root = malloc(sizeof(t_exc_list));
//     if (!root)
//         return (NULL);
//     root->redir = NULL;
//     root->cmd_args = NULL;
//     root->type = type;
//     root->fd.in = -1;
//     root->fd.out = -1;
//     root->next = NULL;
//     return (root);
// }

t_exc_list *new_exc_spot(t_global *global, t_type_node type)
{
    t_exc_list *new;

    new = (t_exc_list *)malloc(sizeof(t_exc_list));
    if (!new)
        malloc_failed(global);
    new->type = type;
    new->redir = NULL;
    new->next = NULL;
    new->fd.in = 0;
    new->fd.out = 1;
    new->cmd_args = NULL;
    return (new);
}

/*void add_cmd_args(t_exc_list *node, char *arg)
{
    t_cmd_args *new;

    new = malloc(sizeof(t_cmd_args));
    if (!new)
        return ;
    new->content = ft_strdup(arg);
    new->next = node->cmd_args;
    node->cmd_args = new;
}*/

t_exc_list *last_exc_node(t_exc_list *head)
{
    if (!head)
        return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}

void    add_back_exc(t_exc_list **head, t_exc_list *new)
{
    t_exc_list  *last_node;

    if (!new && !(*head))
        return ;
    if (!(*head))
        *head = new;
    else
    {
        last_node = last_exc_node((*head));
        last_node->next = new;
    }     
}
