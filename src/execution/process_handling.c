/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:43:34 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/29 17:15:48 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_process(t_shell *shell, int pipe_fd[2], char **args)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (ft_process_error(E_PIPE, &shell->exit_status));
	pid = fork();
	if (pid == -1)
		return (ft_process_error(E_FORK, &shell->exit_status));
	if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_process_error(E_DUP2, shell->exit_status);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_execution(shell, args, shell->env_array);
	}
	else
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2, shell->exit_status);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}
