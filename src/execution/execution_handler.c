/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:13 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/15 15:45:43 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_single_builtin(t_shell *shell, t_command **command)
{
	int	(*func_ptr)(t_shell *, char **);
	int	stdio_fd[2];
	int	status;

	stdio_fd[0] = STDIN_FILENO;
	stdio_fd[1] = STDOUT_FILENO;
	func_ptr = ft_is_builtin((*command)->args);
	status = ft_redirect_handler((*command)->redirs);
	if (status == EXIT_SUCCESS)
		status = func_ptr(shell, (*command)->args);
	return (status);
}

static int	ft_save_stdio_fd(int *stdio_fd)
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

static int	ft_restore_stdio_fd(int *stdio_fd)
{
	if (dup2(stdio_fd[0], STDIN_FILENO) == -1)
		return (1);
	if (dup2(stdio_fd[1], STDOUT_FILENO) == -1)
	{
		close(stdio_fd[0]);
		return (-1);
	}
	close(stdio_fd[1]);
	close(stdio_fd[0]);
	return (1);
}

static void	ft_wait_for_childproc(t_list *open_pids, int *exit_status)
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

int	ft_execution_handler(t_shell *shell, t_command **command)
{
	t_list	*open_pids;
	int		last_exit_status;
	int		stdio_fd[2];

	open_pids = NULL;
	last_exit_status = EXIT_SUCCESS;
	ft_save_stdio_fd(stdio_fd);
	if (!(*command)->next && ft_is_builtin((*command)->args))
		last_exit_status = ft_single_builtin(shell, command);
	else
	{
		last_exit_status = ft_begin_pipeline(shell, command,
				&open_pids, stdio_fd);
		ft_wait_for_childproc(open_pids, &last_exit_status);
	}
	ft_restore_stdio_fd(stdio_fd);
	return (last_exit_status);
}
