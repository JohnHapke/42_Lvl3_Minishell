/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:01:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/06 14:45:03 by iherman-         ###   ########.fr       */
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
		ft_token_handler(line); //TODO
		// Execute tokens (e.g. Pipe if necessary, execute command e.t.c)
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
