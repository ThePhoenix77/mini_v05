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

void    print_exc_list(t_exc_list *head)
{
    t_exc_list *tmp;
    t_cmd_args *cmd;
    t_redir *redi;
    tmp = head;
    while (tmp)
    {
        cmd = tmp->cmd_args;
        redi = tmp->redir;
        if (redi)
        {
            printf("______________redir_________________\n");
            while (redi)
            {
                printf("redircton::::(%s)\n", redi->file_name);
                printf("redi type::::(%d)\n", redi->type);
                redi = redi->next;
            }
            printf("_______________________________\n");
        }    
        if (cmd)
        {    
            printf("____________cmd_________________\n");
            while (cmd)
            {
                printf("command::::(%s)\n", cmd->content);
                cmd = cmd->next;
            }
            printf("_______________________________\n");
            printf("_______________________________\n");
            printf("_______________________________\n");
        }
        tmp = tmp->next;
    }
}

//build execution linkend list
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
        }
        create_node(global, &mv_node);
    }
    // print_exc_list(global->root);
}
