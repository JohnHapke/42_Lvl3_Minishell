/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:38 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/11 17:23:18 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_builtin_error(int code, char *cmd, char *optional, char *messsage)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (optional)
	{
		ft_putstr_fd(optional, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(messsage, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}

int	(*ft_is_builtin(char **args))(t_shell *, char **)
{
	if (ft_strlen(args[0]) == 4 && ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (&ft_echo);
	else if (ft_strlen(args[0]) == 2 && ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (&ft_cd);
	else if (ft_strlen(args[0]) == 3 && ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (&ft_pwd);
	else if (ft_strlen(args[0]) == 7 && ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (&ft_export);
	else if (ft_strlen(args[0]) == 5 && ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (&ft_unset);
	else if (ft_strlen(args[0]) == 3 && ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (&ft_env);
	else if (ft_strlen(args[0]) == 4 && ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (&ft_exit);
	return (NULL);
}

void	ft_clean_subshell_exit(int exit_code, t_command *command, t_shell *shell, t_list **open_pids)
{
	t_env	*current;

	free(shell->env_array);
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

int	ft_builtin_handler(t_shell *shell, t_command *command, int *pipe_fd, t_list **open_pids)
{
	pid_t	*pid;
	int	exit_status;
	int	(*func_ptr)(t_shell *, char **);
	
	exit_status = EXIT_FAILURE;
	if (command->args == NULL || command->args[0] == NULL)
		return (-1);
	func_ptr = ft_is_builtin(command->args);
	if (func_ptr)
	{
		pid = malloc(sizeof(pid_t));
		if (!pid)
			return (ft_other_error(E_MEM, NULL));
		*pid = fork();
		if (*pid == -1)
			/*fuck*/;
		else if (*pid == 0)
		{
			ft_restore_signals();
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				ft_process_error(E_DUP2);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			exit_status = ft_input_handler(command->redirs);
			if (exit_status != EXIT_SUCCESS)
				ft_clean_subshell_exit (exit_status, command, shell, open_pids);
			exit_status = ft_output_handler(command->redirs);
			if (exit_status != EXIT_SUCCESS)
				ft_clean_subshell_exit (exit_status, command, shell, open_pids);
			exit_status = func_ptr(shell, command->args);
			ft_clean_subshell_exit (exit_status, command, shell, open_pids);
		}
		else
		{
			ft_lstadd_back(open_pids, ft_lstnew(pid));
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
				ft_process_error(E_DUP2);
			if (command->next)
			{
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
		}
	}
	else
		return (-1);
	return (EXIT_SUCCESS);
}

int	ft_single_builtin(t_shell *shell, t_command **command)
{
   	int (*func_ptr)(t_shell *, char **);
   	int stdio_fd[2];
   	int status;

	stdio_fd[0] = STDIN_FILENO;
	stdio_fd[1] = STDOUT_FILENO;
	func_ptr = ft_is_builtin((*command)->args);
    status = ft_input_handler((*command)->redirs);
    if (status == EXIT_SUCCESS)
        status = ft_output_handler((*command)->redirs);
    if (status == EXIT_SUCCESS)
        status = func_ptr(shell, (*command)->args);
    return (status);
}
