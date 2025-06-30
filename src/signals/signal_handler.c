/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:12 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/30 16:41:10 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signal_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
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
	ft_set_signal(SIGQUIT, &ft_signal_handler);
	ft_set_signal(SIGSTOP, &ft_signal_handler);
}

void	ft_restore_signals(void)
{
	ft_set_signal(SIGINT, SIG_DFL);
	ft_set_signal(SIGQUIT, SIG_DFL);
	ft_set_signal(SIGSTOP, SIG_DFL);
}