/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/26 16:37:38 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution_handler(t_command *command, t_shell *shell)
{
	int		pipe_fd[2];
	int		stdout_fd;
	int		i;

	stdout_fd = dup(STDOUT_FILENO);
	while (command->next)
	{
		ft_input_handler(command->redirs);
		ft_output_handler(command->redirs);
		ft_process(pipe_fd, command->args, shell);
		command = command->next;
	}
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	ft_input_handler(command->redirs);
	ft_output_handler(command->redirs);
	ft_execution(command->args, shell->env_array);
}
