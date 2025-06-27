/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/27 14:11:50 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_last_command(t_command *command, t_shell *shell)
{
	pid_t	pid;

	if (command != NULL)
	{
		ft_input_handler(command->redirs);
		ft_output_handler(command->redirs);
		pid = fork();
		if (pid == -1)
			ft_error_handler(ERROR_EXIT_FAILURE);
		if (pid == 0)
			ft_execution(command->args, shell->env_array);
		else
			waitpid(pid, NULL, 0);
	}
}

void	ft_execution_handler(t_command *command, t_shell *shell)
{
	int		pipe_fd[2];
	int		stdout_fd;
	int		stdin_fd;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	while (command && command->next)
	{
		ft_input_handler(command->redirs);
		ft_output_handler(command->redirs);
		ft_process(pipe_fd, command->args, shell);
		command = command->next;
	}
	ft_last_command(command, shell);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	close(stdin_fd);
}
