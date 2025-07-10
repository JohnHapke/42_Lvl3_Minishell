/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:43:34 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/10 22:52:20 by iherman-         ###   ########.fr       */
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

int	ft_process(t_shell *shell, t_command *command, int *pipe_fd, t_list **open_pids)
{
	char	*cmd_path;
	pid_t	*pid;

	pid	= malloc(sizeof(pid_t));
	if (!pid)
		return (ft_other_error(E_MEM, NULL));
	cmd_path = ft_get_cmd_path(command->args[0], shell->env_array);
	if (!cmd_path)
		return (ft_command_error(E_CMD, command->args[0]));
	*pid = fork();
	if (*pid == -1)
	{
		free(pid);
		return (ft_process_error(E_FORK));
	}
	if (*pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_process_error(E_DUP2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_execution(command, cmd_path, shell->env_array);
	}
	else
	{
		ft_lstadd_back(open_pids, ft_lstnew(pid));
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2);
		close(pipe_fd[0]);
		free(cmd_path);
	}
	return (EXIT_SUCCESS);
}
