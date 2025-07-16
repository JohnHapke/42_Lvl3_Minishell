/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:06:27 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:26:18 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_last_command(t_shell *shell, t_list **open_pids,
				t_command *cmd)
{
	char	*cmd_path;
	pid_t	*pid;
	int		status;

	status = ft_process_setup(shell, cmd, &pid, &cmd_path);
	if (status != EXIT_SUCCESS)
		return (status);
	if (*pid == 0)
		ft_execution(cmd, cmd_path, shell->env_array);
	free(cmd_path);
	ft_lstadd_back(open_pids, ft_lstnew(pid));
	return (EXIT_SUCCESS);
}

static void	ft_remove_command_node(t_command **command)
{
	t_command	*cmd_temp;
	t_redir		*red_temp;

	if (!command || !*command)
		return ;
	cmd_temp = (*command)->next;
	while ((*command)->redirs)
	{
		free((*command)->redirs->file);
		red_temp = (*command)->redirs->next;
		free((*command)->redirs);
		(*command)->redirs = red_temp;
	}
	ft_free_all((*command)->args);
	free(*command);
	*command = cmd_temp;
}

int	ft_begin_pipeline(t_shell *shell, t_command **command,
		t_list **open_pids, int *stdio_fd)
{
	int			pipe_fd[2];
	int			error;

	error = EXIT_SUCCESS;
	while ((*command) && (*command)->next)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_process_error(E_PIPE));
		error = ft_builtin_handler(shell, *command, pipe_fd, open_pids);
		if (shell->should_exit == true)
			break ;
		if (error == -1)
			error = ft_process(shell, *command, pipe_fd, open_pids);
		if (error != EXIT_SUCCESS)
			break ;
		ft_remove_command_node(command);
	}
	if (shell->should_exit == false && error == EXIT_SUCCESS)
	{
		error = ft_builtin_handler(shell, *command, stdio_fd, open_pids);
		if (error == -1)
			error = ft_last_command(shell, open_pids, *command);
		ft_remove_command_node(command);
	}
	return (error);
}
