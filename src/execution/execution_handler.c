/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 17:01:20 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution_handler(t_command *command, t_shell *shell)
{
	int	fds[2];
	int	i;

	while (command->next)
	{
		ft_input_handler(command->redirs);
		ft_process(fds, command->args, shell);
		ft_output_handler(command->redirs);
		command = command->next;
	}
	ft_execution(command->args, shell->env_array);
}
