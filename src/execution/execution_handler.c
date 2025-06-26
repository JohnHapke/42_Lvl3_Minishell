/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/26 17:22:14 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution_handler(t_command *command, t_shell *shell)
{
	int		pipe_fd[2];
	int		stdout_fd, stdin_fd;
	int		i;
	pid_t	last_command;

	stdout_fd = dup(STDOUT_FILENO);
	stdin_fd = dup(STDIN_FILENO);
	while (command->next)
	{
		ft_input_handler(command->redirs);
		ft_output_handler(command->redirs);
		ft_process(pipe_fd, command->args, shell);
		dup2(stdout_fd, STDOUT_FILENO);
		dup2(stdin_fd, STDIN_FILENO);
		command = command->next;
	}
	ft_input_handler(command->redirs);
	ft_output_handler(command->redirs);
	last_command = fork();
	if (last_command == -1)
		ft_error_handler();
	if (last_command == 0)
		ft_execution(command->args, shell->env_array);
	else
		waitpid(last_command, NULL, 0);
	
	dup2(stdout_fd, STDOUT_FILENO);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdout_fd);//temp
	close(stdin_fd); //temp
}
