/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/10 17:39:50 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_last_command(t_shell *shell, t_list **open_pids, t_command *command)
{
	pid_t	*pid;
	int		error;
	int		status;

	status = 0;
	if (command != NULL)
	{
		error = ft_input_handler(command->redirs);
		if (error != EXIT_SUCCESS)
			return (error);
		error = ft_output_handler(command->redirs, STDOUT_FILENO);
		if (error != EXIT_SUCCESS)
			return (error);
		pid = malloc(sizeof(pid_t));
		if (!pid)
			return (ft_other_error(E_MEM, ""));
		*pid = fork();
		if (*pid == -1)
		{
			free(pid);
			return (ft_process_error(E_FORK));
		}
		if (*pid == 0)
			ft_execution(command->args, shell->env_array);
		ft_lstadd_back(open_pids, ft_lstnew(pid));
	}
	return (EXIT_SUCCESS);
}

static int	ft_restore_stdio_fd(bool restore, int *stdio_fd)
{
	if (restore == false)
	{
		stdio_fd[0] = dup(STDIN_FILENO);
		if (stdio_fd[0] == -1)
			return (1);
		stdio_fd[1] = dup(STDOUT_FILENO);
		if (stdio_fd[1] == -1)
		{
			close(stdio_fd[0]);
			return (-1);
		}
		return (1);
	}
	else //needs error handling
	{
		dup2(stdio_fd[0], STDIN_FILENO);
		dup2(stdio_fd[1], STDOUT_FILENO);
		close(stdio_fd[1]);
		close(stdio_fd[0]);
		return (1);
	}
}

int	ft_external_handler(t_shell *shell, t_list **open_pids, t_command *command, int *pipe_fd)
{
	int	error;

	error = ft_input_handler(command->redirs);
	if (error != EXIT_SUCCESS)
		return (error);
	error = ft_output_handler(command->redirs, STDOUT_FILENO);
	if (error != EXIT_SUCCESS)
		return (error);
	error = ft_process(shell, open_pids, command->args, pipe_fd);
	return (error);
}

int	ft_wait_for_childproc(t_list *open_pids)
{
	int		status;
	pid_t	*pid;

	status = 0;
	if (open_pids)
	{
		while (open_pids)
		{
			pid = (pid_t *)(open_pids->content);
			waitpid(*pid, &status, 0);
			ft_control_waitpid_status(status);
			open_pids = open_pids->next;
		}
		ft_lstclear(&open_pids, &free);
		return (ft_control_waitpid_status(status));
	}
	return (EXIT_SUCCESS);
}

int	ft_execution_handler(t_shell *shell, t_command *command)
{
	t_list	*open_pids;
	int		stdio_fd[2];
	int		pipe_fd[2];
	int		error;

	error = 0;
	open_pids = NULL;
	ft_restore_stdio_fd(false, stdio_fd);
	while (command && command->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_wait_for_childproc(open_pids);
			ft_restore_stdio_fd(true, stdio_fd);
			return (ft_process_error(E_PIPE));
		}
		error = ft_builtin_handler(shell, command, pipe_fd);
		if (shell->should_exit == true)
			break ;
		if (error == -1)
			error = ft_external_handler(shell, &open_pids, command, pipe_fd);
		if (error != EXIT_SUCCESS)
			break;
		command = command->next;
	}
	if (shell->should_exit == false && error == EXIT_SUCCESS)
	{
		error = ft_builtin_handler(shell, command, stdio_fd);
		if (error == -1)
			error = ft_last_command(shell, &open_pids, command);
	}
	error = ft_wait_for_childproc(open_pids);
	ft_restore_stdio_fd(true, stdio_fd);
	return (error);
}
