/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exc_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:57:24 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/10 13:02:24 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_node(t_global *global, t_lst **node)
{
    t_cmd_args  *new_cmd_node;
    t_redir     *new_rd_node;
    t_exc_list  *new_exc_node;
     
    new_exc_node = new_exc_spot(global, CMD);
    add_back_exc(&global->root, new_exc_node);
    while ((*node) && (*node)->type != PIPE)
    {
        while (*node && ((*node)->type == WORD || (*node)->type == ENV))
        {
            new_cmd_node = new_cmd_element(global, (*node)->content);
            add_back_element(&new_exc_node->cmd_args, new_cmd_node);
            (*node) = (*node)->next;
        }
        if (*node && ((*node)->type == REDIR_IN
            || (*node)->type == REDIR_OUT
            || (*node)->type == DREDIR_OUT))
        {
            new_rd_node = new_vertex(global, *node);
            add_back_redir(&new_exc_node->redir, new_rd_node);
            *node = (*node)->next->next;
            while (*node && ((*node)->type == WORD || (*node)->type == ENV))
            {
                new_cmd_node = new_cmd_element(global, (*node)->content);
                add_back_element(&new_exc_node->cmd_args, new_cmd_node);
                (*node) = (*node)->next;
            }
        }
    }
}
