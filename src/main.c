/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/11 16:45:54 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	(void) argc;
	ft_shell_init(&shell, envp);
	ft_init_signals();
	ft_shell_loop(&shell);
	ft_cleanup_shell(&shell);
	rl_clear_history();
	return (shell.exit_status);
}
