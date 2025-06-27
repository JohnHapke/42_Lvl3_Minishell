/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/27 15:10:05 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_last_command(t_shell *shell, t_command *command)
{
	pid_t	pid;

	if (command != NULL)
	{
		ft_input_handler(shell, command->redirs);
		ft_output_handler(shell, command->redirs);
		pid = fork();
		if (pid == -1)
			ft_error_handler(ERROR_EXIT_FAILURE, &shell->exit_status);
		if (pid == 0)
			ft_execution(shell, command->args, shell->env_array);
		else
			waitpid(pid, NULL, 0);
	}
}

void	ft_execution_handler(t_shell *shell, t_command *command)
{
	int		pipe_fd[2];
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	while (command && command->next)
	{
		ft_input_handler(shell, command->redirs);
		ft_output_handler(shell, command->redirs);
		ft_process(shell, pipe_fd, command->args);
		command = command->next;
	}
	ft_last_command(shell, command);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	close(stdin_fd);
}
