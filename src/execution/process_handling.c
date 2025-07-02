/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:43:34 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/02 16:33:21 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_control_waitpid_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	ft_process(t_shell *shell, char **args, int *pipe_fd)
{
	pid_t	pid;
	int		status[1];

	pid = fork();
	if (pid == -1)
		return (ft_process_error(E_FORK));
	if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_process_error(E_DUP2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_execution(args, shell->env_array);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2);
		close(pipe_fd[0]);
		waitpid(pid, status, 0);
	}
	return (ft_control_waitpid_status(*status));
}
