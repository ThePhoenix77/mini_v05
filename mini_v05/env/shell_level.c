/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:34:52 by eaboudi           #+#    #+#             */
/*   Updated: 2024/08/31 13:04:51 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atoi_shlvl(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (ft_isspace2(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*str++ == '-');
	while (ft_isdigit(*str))
		num = num * 10 + *str++ - '0';
	if (ft_issign(*str))
		return (LONG_MAX);
	return (num * sign);
}

int     check_shell_level(t_env_list **node, int  num)
{
    if (num == 999)
    {
        free((*node)->content);
        (*node)->content = ft_strdup("SHLVL=");
        if (!(*node)->content)
            return (-1);
        return (-2);
    }    
    num += 1;
    if (num < 0)
        num = 0;
    else if (num > 1000)
    {
        printf("minishell: warning: shell level (%d)", num);
        printf(" too high, resetting to 1\n");
        num = 1;
    }
   return (num);
}

bool    shell_level(t_global *global)
{
    t_env_list  *tmp;
    char        *ptr_num;
    int         num;
    
    tmp = get_var_env(global, "SHLVL=");
    ptr_num = ft_strchr(tmp->content, '=');
    num = ft_atoi_shlvl(ptr_num + 1);
    num = check_shell_level(&tmp, num);
    if (num == -1)
        return (FAILURE);
    if (num == -2)
       return (SUCCESS); 
    ptr_num = ft_itoa(num);
    if (!ptr_num)
        return (FAILURE);
    if (update_env(&tmp, ptr_num) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

