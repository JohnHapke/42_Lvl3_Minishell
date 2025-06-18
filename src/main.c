/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/18 14:27:13 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_handler(void)
{
	printf("Error!\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	(void) argc;
	ft_shell_init(&shell, envp);
	ft_shell_loop(&shell);
	//ft_cleanup_shell(&shell);
	return (0);
}
