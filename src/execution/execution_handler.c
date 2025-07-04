/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/04 16:36:58 by iherman-         ###   ########.fr       */
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
		error = ft_output_handler(command->redirs, STDOUT_FILENO);
		if (error != 0)
			return (error);
		pid = fork();
		if (pid == -1)
			return (ft_process_error(E_FORK));
		if (pid == 0)
			ft_execution(command->args, shell->env_array);
		else
			waitpid(pid, &status, 0);
		return (ft_control_waitpid_status(status));
	}
	return (EXIT_SUCCESS);
}

static int	ft_restore_stdio_fd(bool restore, int *stdio_fd)
{
	int			dup_error; //dup error unused
	
	dup_error = 1;
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
	else
	{
		dup_error = dup2(stdio_fd[0], STDIN_FILENO); //need to print error message if fails. also return from execution_handler
		dup_error = dup2(stdio_fd[1], STDOUT_FILENO);
		close(stdio_fd[1]);
		close(stdio_fd[0]);
		return (dup_error);
	}
}

int	ft_external_handler(t_shell *shell, t_command *command, int *pipe_fd)
{
	int	error;

	if (ft_input_handler(command->redirs) == -1)
		return (ERROR_EXIT_FAILURE);
	error = ft_output_handler(command->redirs, STDOUT_FILENO);
	if (error != 0)
		return (error);
	error = ft_process(shell, command->args, pipe_fd);
	return (error);
}

int	ft_execution_handler(t_shell *shell, t_command *command)
{
	int	stdio_fd[2];
	int	pipe_fd[2];
	int	error;

	error = 0;
	ft_restore_stdio_fd(false, stdio_fd);
	while (command && command->next)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_process_error(E_PIPE));
		error = ft_builtin_handler(shell, command, pipe_fd);
		if (error == -2)
			break ;
		if (error == -1)
			error = ft_external_handler(shell, command, pipe_fd);
		command = command->next;
	}
	if (error != -2)
	{
		error = ft_builtin_handler(shell, command, stdio_fd);
		if (error == -1)
			error = ft_last_command(shell, command);
	}
	ft_restore_stdio_fd(true, stdio_fd);
	return (error);
}
