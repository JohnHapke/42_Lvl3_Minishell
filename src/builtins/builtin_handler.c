/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:38 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:19:37 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*ft_is_builtin(char **args))(t_shell *s, char **c)
{
	if (!args || !args[0])
		return (NULL);
	if (ft_strlen(args[0]) == 4 && ft_strncmp(args[0], "echo",
			ft_strlen(args[0])) == 0)
		return (&ft_echo);
	else if (ft_strlen(args[0]) == 2 && ft_strncmp(args[0], "cd",
			ft_strlen(args[0])) == 0)
		return (&ft_cd);
	else if (ft_strlen(args[0]) == 3 && ft_strncmp(args[0], "pwd",
			ft_strlen(args[0])) == 0)
		return (&ft_pwd);
	else if (ft_strlen(args[0]) == 6 && ft_strncmp(args[0], "export",
			ft_strlen(args[0])) == 0)
		return (&ft_export);
	else if (ft_strlen(args[0]) == 5 && ft_strncmp(args[0], "unset",
			ft_strlen(args[0])) == 0)
		return (&ft_unset);
	else if (ft_strlen(args[0]) == 3 && ft_strncmp(args[0], "env",
			ft_strlen(args[0])) == 0)
		return (&ft_env);
	else if (ft_strlen(args[0]) == 4 && ft_strncmp(args[0], "exit",
			ft_strlen(args[0])) == 0)
		return (&ft_exit);
	return (NULL);
}

void	ft_clean_subshell_exit(int exit_code, t_command *command,
			t_shell *shell, t_list **open_pids)
{
	t_env	*current;

	ft_free_all(shell->env_array);
	while (shell->env_list)
	{
		free(shell->env_list->key);
		free(shell->env_list->value);
		current = shell->env_list->next;
		free(shell->env_list);
		shell->env_list = current;
	}
	while (shell->user_env_list)
	{
		free(shell->user_env_list->key);
		free(shell->user_env_list->value);
		current = shell->user_env_list->next;
		free(shell->user_env_list);
		shell->user_env_list = current;
	}
	ft_lstclear(open_pids, &free);
	ft_command_lstclear(&command);
	exit(exit_code);
}

int	ft_builtin_child(t_shell *shell, t_command *command, int *pipe_fd)
{
	int		exit_status;
	int		(*func_ptr)(t_shell *, char **);

	func_ptr = ft_is_builtin(command->args);
	exit_status = EXIT_SUCCESS;
	ft_restore_signals();
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		ft_process_error(E_DUP2);
	ft_close_pipe(pipe_fd);
	exit_status = ft_redirect_handler(command->redirs);
	if (exit_status != EXIT_SUCCESS)
		return (exit_status);
	exit_status = func_ptr(shell, command->args);
	return (exit_status);
}

int	ft_execute_builtin(t_shell *shell, t_command *command,
		int *pipe_fd, t_list **open_pids)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t));
	if (!pid)
		return (ft_other_error(E_MEM, NULL));
	*pid = fork();
	if (*pid == -1)
	{
		free (pid);
		return (ft_other_error(E_FORK, command->args[0]));
	}
	else if (*pid == 0)
		ft_clean_subshell_exit (ft_builtin_child(shell, command, pipe_fd),
			command, shell, open_pids);
	ft_lstadd_back(open_pids, ft_lstnew(pid));
	return (EXIT_SUCCESS);
}

int	ft_builtin_handler(t_shell *shell, t_command *command,
		int *pipe_fd, t_list **open_pids)
{
	int		exit_status;

	exit_status = EXIT_FAILURE;
	if (command->args == NULL || command->args[0] == NULL)
		return (-1);
	if (ft_is_builtin(command->args))
	{
		exit_status = ft_execute_builtin(shell, command, pipe_fd, open_pids);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			ft_process_error(E_DUP2);
		if (command->next)
			ft_close_pipe(pipe_fd);
		return (exit_status);
	}
	else
		return (-1);
	return (EXIT_SUCCESS);
}
