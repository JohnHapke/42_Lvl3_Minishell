/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:22 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/09 16:27:31 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *shell, char **argv, int *pipe_fd)
{
	int	i;

	(void) argv;
	(void) shell;
	i = 0;
	shell->should_exit = true;
	write(pipe_fd[1], "exit\n", 5);
	if (argv[1])
	{
		while (argv[1][i])
		{
			if (!(ft_isdigit(argv[1][i])))
			{
				write(2, "minishell: exit: ", 18);
				write(2, argv[i], ft_strlen(argv[i]));
				write(2,  "numeric argument required\n", 27);
				return (ERROR_USAGE);
			}
			i++;
		}
		return (ft_atoi(argv[1]));
	}
	else
		return (shell->exit_status);
}
