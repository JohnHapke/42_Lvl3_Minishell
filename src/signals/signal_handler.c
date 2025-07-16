/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:12 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 08:27:03 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (rl_done == 0)
			rl_redisplay();
	}
}

void	ft_set_signal(int sig_type, void (*handler)(int))
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof (struct sigaction));
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, sig_type);
	action.sa_flags = SA_RESTART;
	sigaction(sig_type, &action, NULL);
}

void	ft_init_signals(void)
{
	ft_set_signal(SIGINT, &ft_signal_handler);
	ft_set_signal(SIGQUIT, SIG_IGN);
}

void	ft_restore_signals(void)
{
	ft_set_signal(SIGINT, SIG_DFL);
	ft_set_signal(SIGQUIT, SIG_DFL);
}
