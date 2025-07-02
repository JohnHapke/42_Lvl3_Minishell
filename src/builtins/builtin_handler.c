/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:38 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/02 17:10:51 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	(*ft_is_builtin(char **args))(t_shell *shell, char **args, int *pipe_fd)
{
	if (ft_strlen(args[0]) && ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (&ft_echo);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (&ft_cd);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (&ft_pwd);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (&ft_export);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (&ft_unset);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (&ft_env);
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (&ft_exit);
	return (NULL);
}

int	ft_builtin_handler(t_shell *shell, t_command *command, int *pipe_fd)
{
	int	exit_status;

	int	(*func_ptr)(t_shell *shell, char **args, int *pipe_fd);

	exit_status = EXIT_FAILURE;
	func_ptr = ft_is_builtin(command->args);
	if (func_ptr)
	{
		ft_output_handler(command->redirs, pipe_fd[1]);
		exit_status = func_ptr(shell, command->args, pipe_fd);
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2);
		close(pipe_fd[0]);
	}
	return (exit_status);
}
