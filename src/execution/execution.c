/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:02:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/11 13:49:32 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution(t_command *command, char *cmd_path, char **env)
{
	int		io_error;

	ft_restore_signals();
	io_error = ft_input_handler(command->redirs);
	if (io_error != EXIT_SUCCESS)
		exit (io_error);
	io_error = ft_output_handler(command->redirs);
	if (io_error != EXIT_SUCCESS)
		exit (io_error);
	if (!command->args || !command->args[0])
		exit(EXIT_SUCCESS);
	if (!cmd_path)
		exit(ft_command_error(E_CMD, command->args[0]));
	execve(cmd_path, command->args, env);
	free(cmd_path);
	if (errno == EACCES)
		exit(ft_command_error(E_PERMISSION, command->args[0]));
	else
		exit(ft_other_error(E_OTHER, command->args[0]));
}
