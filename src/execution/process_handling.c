/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:43:34 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/15 15:18:25 by iherman-         ###   ########.fr       */
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

void	ft_close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

int	ft_process_setup(t_shell *shell, t_command *cmd,
		pid_t **pid, char **cmd_path)
{
	*cmd_path = ft_get_cmd_path(cmd->args[0], shell->env_array);
	if (!*cmd_path)
		return (ft_command_error(E_CMD, cmd->args[0]));
	if (access(*cmd_path, X_OK) != 0)
	{
		free(*cmd_path);
		return (ft_command_error(E_PERMISSION, cmd->args[0]));
	}
	*pid = malloc(sizeof (pid_t));
	if (!*pid)
	{
		free(*cmd_path);
		return (ft_other_error(E_MEM, NULL));
	}
	**pid = fork();
	if (**pid == -1)
	{
		free(*pid);
		free(*cmd_path);
		return (ft_process_error(E_FORK));
	}
	return (EXIT_SUCCESS);
}

int	ft_process(t_shell *shell, t_command *cmd, int *pipe_fd,
		t_list **open_pids)
{
	char	*cmd_path;
	pid_t	*pid;
	int		status;

	status = ft_process_setup(shell, cmd, &pid, &cmd_path);
	if (status != EXIT_SUCCESS)
		return (status);
	if (*pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_process_error(E_DUP2);
		ft_close_pipe(pipe_fd);
		ft_execution(cmd, cmd_path, shell->env_array);
	}
	else
	{
		ft_lstadd_back(open_pids, ft_lstnew(pid));
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2);
		ft_close_pipe(pipe_fd);
		free(cmd_path);
	}
	return (EXIT_SUCCESS);
}
