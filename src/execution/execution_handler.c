/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/30 15:36:15 by jhapke           ###   ########.fr       */
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
			ft_execution(command->args, shell->env_array);
		else
			waitpid(pid, &status, 0);
		return (ft_control_waitpid_status(status));
	}
	return (EXIT_SUCCESS);
}

int	ft_execution_handler(t_shell *shell, t_command *command)
{
	int	pipe_fd[2];
	int	stdout_fd;
	int	stdin_fd;
	int	error;

	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd == -1)
		return (ft_process_error(E_DUP));
	stdin_fd = dup(STDIN_FILENO);
	if (stdin_fd == -1)
		return (ft_process_error(E_DUP));
	while (command && command->next)
	{
		if (ft_input_handler(command->redirs) == -1)
			return (ERROR_EXIT_FAILURE);
		error = ft_output_handler(command->redirs);
		if (error != 0)
			return (error);
		if (ft_process(shell, pipe_fd, command->args) == 1)
			return (ERROR_EXIT_FAILURE);
		command = command->next;
	}
	error = ft_last_command(shell, command);
	if (error != 0)
		return (error);
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		ft_process_error(E_DUP2);
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		ft_process_error(E_DUP2);
	close(stdout_fd);
	close(stdin_fd);
	return (EXIT_SUCCESS);
}
