/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:43:34 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/26 16:29:23 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_process(int pipe_fd[2], char **args, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_handler();
	if (pipe(pipe_fd) == -1)
		ft_error_handler();
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_execution(args, shell->env_array);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}
