/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_step_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:00:47 by eaboudi           #+#    #+#             */
/*   Updated: 2024/08/31 14:30:56 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    special_expand(t_global *global, t_lst **node)
{
    t_expand_list   *tmp;

    tmp = global->exp_head;
    while (tmp)
    {
        
        // if (tmp->content[1] == '?')
        // {
        //    update_line(&tmp->content, 2, global);
        //    //join the exit status.
        //    return (SUCCESS);
        // }
        if (ft_isdigit(tmp->content[1]))
        {    
            update_line(&tmp->content, 2, global);
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }
    return (FAILURE);
}

void    join_result(t_global *global)
{
    char            *tmp_str;
    t_expand_list   *tmp;

    tmp = global->exp_head;
    global->content = NULL;
    while (tmp)
    {
        if (!tmp->content && !global->content)
        {
            tmp  = tmp->next;
            continue ;
        }
        tmp_str = ft_strjoin2(global->content, tmp->content);
        if (!tmp_str)
        {
            if (global->content)
                free(global->content);
            malloc_failed(global);
        }
        if (global->content)
            free(global->content);
        global->content = ft_strdup(tmp_str);
        free(tmp_str);
        tmp = tmp->next;
    }
}

void finish_exp(t_global *global, t_lst **node)
{
    if ((*node)->content)
        free((*node)->content);
    join_result(global);
    (*node)->content = ft_strdup(global->content);
    if (global->content)
        free(global->content);
    free_exp_list(&global->exp_head);
}
