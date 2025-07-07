/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:02:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/07 15:45:27 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execution(char **args, char **env)
{
	char	*cmd_path;

	ft_restore_signals();
	if (!args || !args[0])
		exit(EXIT_SUCCESS);
	cmd_path = ft_get_cmd_path(args[0], env);
	if (!cmd_path)
		exit(ft_command_error(E_CMD, args[0]));
	execve(cmd_path, args, env);
	free(cmd_path);
	if (errno == EACCES)
		exit(ft_command_error(E_PERMISSION, args[0]));
	else
		exit(ft_other_error(E_OTHER, args[0]));
}
