/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:58:42 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/30 15:39:00 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_process_error(t_exec_error error)
{
	if (error == E_FORK)
	{
		perror("./minishell: fork");
		return (ERROR_EXIT_FAILURE);
	}
	if (error == E_PIPE)
	{
		perror("./minishell: pipe");
		return (ERROR_EXIT_FAILURE);
	}
	if (error == E_DUP)
	{
		perror("./minishell: dup");
		return (ERROR_EXIT_FAILURE);
	}
	if (error == E_DUP2)
	{
		perror("./minishell: dup2");
		return (ERROR_EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_command_error(t_exec_error error, char *cmd)
{
	if (error == E_CMD)
	{
		ft_putstr_fd("./minishell: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return (ERROR_CMD_NOT_FOUND);
	}
	else if (error == E_PERMISSION)
	{
		ft_putstr_fd("./minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": PERMISSION DENIED\n", 2);
		return (ERROR_CMD_NOT_EXECUTABLE);
	}
	return (EXIT_SUCCESS);
}

int	ft_other_error(t_exec_error error, char *arg)
{
	if (error == E_OPEN || error == E_OTHER)
	{
		ft_putstr_fd("./minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (ERROR_EXIT_FAILURE);
	}
	else if (error == E_MEM)
	{
		ft_putstr_fd("./minishell: cannot allocate memory\n", 2);
		return (ERROR_MEMORY_ALLOC);
	}
	return (EXIT_SUCCESS);
}
