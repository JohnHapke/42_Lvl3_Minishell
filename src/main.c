/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/10 14:53:27 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		ft_token_handler(line);
		// TODO
		add_history(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	(void) argc;
	ft_init_shell(&shell, envp);
	ft_shell_loop(&shell);
	ft_cleanup_shell(&shell);
}
