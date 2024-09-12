/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:08:18 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/06 20:04:41 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(t_global *global, char **env)
{
	global->env = env;
	global->head = NULL;
	global->content = NULL;
	global->list_len = 0;
	global->env_list = NULL;
	global->env_list = NULL;
	global->pre_head = NULL;
	global->exp_head = NULL;
	global->here_doc_num = 0;
	global->root = NULL;
}

int	check_valid_in(t_global *global)
{
	if (!global->line_input)
		return (FAILURE);
	if (global->line_input[0] == '\0')
	{	
		free(global->line_input);
		return(SUCCESS);
	}
	return (2);
}

int		ft_strlen_un_char(char *str, char c)		//count until find value of c
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-2);
}

int		ft_strlen_un_del(char *sep, char *str)		//count until find a seprator from sep in str
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (-1);
	if (ft_strchr(sep, str[0]))
		return (1);
	while (str[i])
	{
		j = 0;
		while (sep[j])
		{
			if (sep[j] == str[i])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}


int ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}
