/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:05 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/07 15:34:48 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_shell *shell, char **argv, int *pipe_fd)
{
	t_env	*current;

	(void) pipe_fd;
	(void) argv;
	current = shell->env_list;
	while (current)
	{
		ft_putstr_fd(current->key, pipe_fd[1]);
		ft_putchar_fd('=', pipe_fd[1]);
		ft_putstr_fd(current->value, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
