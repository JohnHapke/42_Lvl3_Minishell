/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/11 17:24:26 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_last_command(t_shell *shell, t_list **open_pids, t_command *command)
{
	char	*cmd_path;
	pid_t	*pid;
	int		status;

	status = 0;
	cmd_path = ft_get_cmd_path(command->args[0], shell->env_array);
	if (!cmd_path)
		return (ft_command_error(E_CMD, command->args[0]));
	if (access(cmd_path, X_OK) != 0)
	{
		free(cmd_path);
		return (ft_command_error(E_PERMISSION, command->args[0]));
	}
	pid = malloc(sizeof(pid_t));
	if (!pid)
		return (ft_other_error(E_MEM, ""));
	*pid = fork();
	if (*pid == -1)
	{
		free(pid);
		return (ft_process_error(E_FORK));
	}
	if (*pid == 0)
	{
		ft_execution(command, cmd_path, shell->env_array);
	}
	free(cmd_path);
	ft_lstadd_back(open_pids, ft_lstnew(pid));
	return (EXIT_SUCCESS);
}

static int	ft_restore_stdio_fd(bool restore, int *stdio_fd)
{
	if (restore == false)
	{
		stdio_fd[0] = dup(STDIN_FILENO);
		if (stdio_fd[0] == -1)
			return (1);
		stdio_fd[1] = dup(STDOUT_FILENO);
		if (stdio_fd[1] == -1)
		{
			close(stdio_fd[0]);
			return (-1);
		}
		return (1);
	}
	else //needs error handling
	{
		dup2(stdio_fd[0], STDIN_FILENO);
		dup2(stdio_fd[1], STDOUT_FILENO);
		close(stdio_fd[1]);
		close(stdio_fd[0]);
		return (1);
	}
}

void	ft_wait_for_childproc(t_list *open_pids, int *exit_status)
{
	t_list	*current;
	int		status;
	pid_t	*pid;

	status = 0;
	current = open_pids;
	if (open_pids)
	{
		while (current)
		{
			pid = (pid_t *)(current->content);
			waitpid(*pid, &status, 0);
			ft_control_waitpid_status(status);
			current = current->next;
		}
		if (!*exit_status)
			*exit_status = ft_control_waitpid_status(status);
		ft_lstclear(&open_pids, &free);
	}
	return ;
}

void	ft_remove_command_node(t_command **command)
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

int	ft_begin_pipeline(t_shell *shell, t_command **command, int *stdio_fd)
{
	t_list		*open_pids;
	int			pipe_fd[2];
	int			error;

	error = EXIT_SUCCESS;
	open_pids = NULL;
	while ((*command) && (*command)->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_wait_for_childproc(open_pids, &error);
			ft_restore_stdio_fd(true, stdio_fd);
			return (ft_process_error(E_PIPE));
		}
		error = ft_builtin_handler(shell, *command, pipe_fd, &open_pids);
		if (shell->should_exit == true)
			break ;
		if (error == -1)
			error = ft_process(shell, *command, pipe_fd, &open_pids);
		if (error != EXIT_SUCCESS)
			break ;
		ft_remove_command_node(command);
	}
	if (shell->should_exit == false && error == EXIT_SUCCESS)
	{
		error = ft_builtin_handler(shell, *command, stdio_fd, &open_pids);
		if (error == -1)
			error = ft_last_command(shell, &open_pids, *command);
		ft_remove_command_node(command);
	}
	ft_wait_for_childproc(open_pids, &error);
	return (error);
}

int	ft_execution_handler(t_shell *shell, t_command **command)
{
	int	last_exit_status;
	int	stdio_fd[2];;
	
	last_exit_status = EXIT_SUCCESS;
	ft_restore_stdio_fd(false, stdio_fd);
	if (!(*command)->next && ft_is_builtin((*command)->args))
	{
		last_exit_status = ft_single_builtin(shell, command);
		ft_remove_command_node(command);
	}
	else
		last_exit_status = ft_begin_pipeline(shell, command, stdio_fd);
	ft_restore_stdio_fd(true, stdio_fd);
	return (last_exit_status);
}
