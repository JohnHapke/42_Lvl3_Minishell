/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:38 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/02 16:21:58 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_shell *shell, char **argv, int *pipe_fd)
{
	bool	newline;
	int		i;

	i = 1;
	(void) shell;
	newline = true;
	if (argv[1] && ft_strlen(argv[1]) == 2 && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		newline = false;
		i = 2;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], pipe_fd[1]);
		if (argv[i + 1])
			ft_putchar_fd(' ', pipe_fd[1]);
		i++;
	}
	if (newline == true)
		ft_putchar_fd('\n', pipe_fd[1]);
	return (EXIT_SUCCESS);
}
