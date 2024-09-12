/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:52:43 by eaboudi           #+#    #+#             */
/*   Updated: 2024/09/10 10:52:21 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*struct sigaction {
    void (*sa_handler)(int);  Signal handler 
    void (*sa_sigaction)(int, siginfo_t *, void *); Alternate signal handler 
    sigset_t sa_mask;         Signal mask 
    int sa_flags;             Flags 
    void (*sa_restorer)(void); Restorer function
};*/

typedef struct sigaction t_sigaction;

void	*ft_memset2(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void signals_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
    {
        signal(SIGQUIT, SIG_IGN);
    }
}

void mask_and_catch_signals(t_sigaction *sig)
{
    sig->sa_handler = signals_handler;

    sigemptyset(&sig->sa_mask);
    sigaddset(&sig->sa_mask, SIGINT);
    sigaddset(&sig->sa_mask, SIGQUIT);
    sigaction(SIGINT, sig, NULL);
    sigaction(SIGQUIT, sig, NULL);
}

void init_sigaction()
{
    t_sigaction sig;

    ft_memset2(&sig, 0, sizeof(sig));
    mask_and_catch_signals(&sig);
}
