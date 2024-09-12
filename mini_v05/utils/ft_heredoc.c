/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:17:32 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/08 18:12:40 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handler(int sig)
{
    if (sig == SIGINT)
    {
        signal(SIGINT, SIG_IGN);
        close(0);
        init_sigaction();
    }
}

void    buff_heredoc(t_global *global, char *line)
{
    char    *tmp;
    char    *save;

    tmp = ft_strjoin2(line, "\n");
    if (!tmp)
    {    
        free(line);
        malloc_failed(global);
    }
    free(line);
    save = ft_strjoin2(global->content, tmp);
    if (global->content)
        free(global->content);
    free(tmp);
    global->content = save;
}
bool    open_heredoc(t_global *global, t_lst *lim_node)
{
    char    *line;

    global->content = NULL;
    signal(SIGINT, handler);
    while (1)
    {
        line = readline("> ");
		if (!ttyname(0))
		{
			open(ttyname(2), O_RDWR);
            return (free(line), FAILURE);
		}
        if (!line || ft_strcmp(line, lim_node->content) == 0)
		{
            free(lim_node->content);
            lim_node->content = global->content;
            if (!line)
                empty_here_doc(global, lim_node);
            free(line);
            break ;
        }
        buff_heredoc(global, line);
    }
    signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
    return (SUCCESS);
}


bool    check_heredoc(t_global *global)
{
    t_lst   *tmp;
    int     fd;

    tmp = global->head;
    while (tmp)
    {
        if (tmp->type == HERE_DOC)
        {  
            if (tmp->next->type == WORD)
                tmp = tmp->next;
            else
                tmp = tmp->next->next;
            if (open_heredoc(global, tmp) == FAILURE)
            {  
                if (global->content)
                    free(global->content);
                return (FAILURE);
            }
            tmp->type = EXP_HERE_DOC;
        }
        tmp = tmp->next;
    }
    return (SUCCESS);
}
