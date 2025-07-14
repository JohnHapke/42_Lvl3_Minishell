/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/14 19:05:54 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_ofile(t_redir *redir, int *file_fd, int out)
{
	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) != 0)
	{
		ft_other_error(E_OTHER, redir->file);
		return (1);
	}
	if (redir->type == REDIR_OUT)
		*file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		*file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*file_fd == -1)
	{
		ft_other_error(E_OPEN, redir->file);
		return (1);
	}
	if (dup2(*file_fd, out) == -1)
	{
		ft_other_error(E_OTHER, redir->file);
		return (1);
	}
	return (0);
}

int	ft_output_handler(t_redir *redir)
{
	int		file_fd;
	bool	error;

	error = false;
	file_fd = -1;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (ft_get_ofile(redir, &file_fd, STDOUT_FILENO))
				error = true;
			close(file_fd);
			if (error)
				return (true);
		}
		redir = redir->next;
	}
	return (error);
}
