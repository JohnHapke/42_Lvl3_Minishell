/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/14 15:55:14 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	(void) argc;
	ft_shell_init(&shell, envp);
	ft_shell_loop(&shell);
	ft_cleanup_shell(&shell);
}
