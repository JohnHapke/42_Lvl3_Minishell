/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:58:42 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 08:25:58 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_error(t_exec_error error)
{
	if (error == E_FORK)
		perror("./minishell: fork");
	if (error == E_PIPE)
		perror("./minishell: pipe");
	if (error == E_DUP)
		perror("./minishell: dup");
	if (error == E_DUP2)
		perror("./minishell: dup2");
	return (ERROR_EXIT_FAILURE);
}

int	ft_command_error(t_exec_error error, char *cmd)
{
	if (error == E_CMD)
	{
		ft_putstr_fd("./minishell: command not found: ", 2);
		if (cmd)
			ft_putendl_fd(cmd, 2);
		else
			ft_putstr_fd("\n", 2);
		return (ERROR_CMD_NOT_FOUND);
	}
	else if (error == E_PERMISSION)
	{
		ft_putstr_fd("./minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
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
		ft_putendl_fd(strerror(errno), 2);
		return (ERROR_EXIT_FAILURE);
	}
	else if (error == E_MEM)
	{
		ft_putstr_fd("./minishell: failed to allocate memory\n", 2);
		return (ERROR_MEMORY_ALLOC);
	}
	return (EXIT_SUCCESS);
}
