/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/14 19:05:34 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

static int	ft_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
		ft_process_error(E_PIPE);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
				&& ft_strlen(line) - 1 == ft_strlen(delimiter)))
		{
			free (line);
			break ;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		free (line);
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}

static int	ft_get_ifile(t_redir *redir, int *file_fd)
{
	if (redir->type != REDIR_HEREDOC && access(redir->file, R_OK) != 0)
	{
		ft_other_error(E_OTHER, redir->file);
		return (1);
	}
	if (redir->type == REDIR_HEREDOC)
		*file_fd = ft_heredoc(redir->file);
	else if (redir->type == REDIR_IN && access(redir->file, R_OK) == 0)
		*file_fd = open(redir->file, O_RDONLY);
	if (*file_fd == -1)
	{
		ft_other_error(E_OPEN, redir->file);
		return (1);
	}
	if (dup2(*file_fd, STDIN_FILENO) == -1)
	{
		ft_other_error(E_OTHER, redir->file);
		return (1);
	}
	return (0);
}

bool	ft_input_redirect(t_redir *redir, t_redir_type mode)
{
	int		file_fd;
	bool	error;

	error = false;
	file_fd = -1;
	while (redir)
	{
		if (redir->type == mode)
		{
			if (ft_get_ifile(redir, &file_fd))
				error = true;
			close(file_fd);
			if (error)
				return (true);
		}
		redir = redir->next;
	}
	return (false);
}

int	ft_input_handler(t_redir *redir)
{
	if (ft_input_redirect(redir, REDIR_HEREDOC))
		return (EXIT_FAILURE);
	if (ft_input_redirect(redir, REDIR_IN))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
