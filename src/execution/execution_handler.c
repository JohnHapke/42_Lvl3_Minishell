/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/01 16:43:33 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_last_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		error;
	int		status;

	status = 0;
	if (command != NULL)
	{
		if (ft_input_handler(command->redirs) == 1)
			return (ERROR_EXIT_FAILURE);
		error = ft_output_handler(command->redirs);
		if (error != 0)
			return (error);
		pid = fork();
		if (pid == -1)
			return (ft_process_error(E_FORK));
		if (pid == 0)
			ft_execution(shell, command->args, shell->env_array);
		else
			waitpid(pid, &status, 0);
		return (ft_control_waitpid_status(status));
	}
	return (EXIT_SUCCESS);
}

static int	ft_restore_stdio_fd(bool restore)
{
	static int	stdio_fd[2];
	int			dup_error;
	
	dup_error = 1;
	if (restore == false)
	{
		if (dup2(STDIN_FILENO, stdio_fd[0]) == -1)
			return (-1);
		if (dup2(STDOUT_FILENO, stdio_fd[1]) == -1)
		{
			close(stdio_fd[0]);
			return (-1);
		}
		return (1);
	}
	else
	{
		dup_error = dup2(stdio_fd[0], STDIN_FILENO);
		dup_error = dup2(stdio_fd[1], STDOUT_FILENO);
		close(stdio_fd[1]);
		close(stdio_fd[0]);
		return (dup_error);
	}
}

int	ft_execution_handler(t_shell *shell, t_command *command)
{
	int	pipe_fd[2];
	
	int	error;

	if (ft_restore_stdio_fd(0) != 1)
		ft_process_error(E_DUP2);
	while (command && command->next)
	{
		if (ft_input_handler(command->redirs) == -1)
			return (ERROR_EXIT_FAILURE);
		error = ft_output_handler(command->redirs);
		if (error != 0)
			return (error);
		error = ft_builtin_handler(shell, command->args);
		if (error == EXIT_SUCCESS)
			error = ft_process(shell, pipe_fd, command->args);
		command = command->next;
	}
	error = ft_builtin_handler(shell, command->args);
	if (error == EXIT_SUCCESS)
		error = ft_last_command(shell, command);
	if (ft_restore_stdio_fd(1) != 1)
		ft_process_error(E_DUP2);
	return (error);
}
