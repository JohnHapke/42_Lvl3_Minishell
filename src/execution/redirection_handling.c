/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 18:15:56 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*assume function is never called with wrong redir type*/
static int	ft_get_ifile(t_redir *redir)
{
	int	file_fd;

	if (access(redir->file, F_OK) != 0 || access(redir->file, R_OK))
		return (ft_other_error(E_OTHER, redir->file));
	else
		file_fd = open(redir->file, O_RDONLY);
	if (file_fd == -1)
		return (ft_other_error(E_OPEN, redir->file));
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		close(file_fd);
		return (ft_other_error(E_OTHER, redir->file));
	}
	close (file_fd);
	return (0);
}

/*... again, assume function is never called with wrong redir type*/
static int	ft_get_ofile(t_redir *redir)
{
	int	file_fd;

	if (access(redir->file, F_OK) == 0 && access(redir->file, W_OK) != 0)
		return (ft_other_error(E_OTHER, redir->file));
	if (redir->type == REDIR_OUT)
		file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
		return (ft_other_error(E_OPEN, redir->file));
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		close(file_fd);
		return (ft_other_error(E_OTHER, redir->file));
	}
	close(file_fd);
	return (0);
}

bool	ft_heredoc_redirect(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			fd = ft_heredoc(redir->file);
			if (fd == -1)
				return (ft_other_error(E_OPEN, redir->file));
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (ft_other_error(E_OTHER, redir->file));
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (false);
}

int	ft_redirect_handler(t_redir *redir)
{
	int	error;

	error = false;
	if (ft_heredoc_redirect(redir))
		return (EXIT_FAILURE);
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (ft_get_ofile(redir))
				return (ERROR_EXIT_FAILURE);
		}
		else if (redir->type == REDIR_IN)
		{
			if (ft_get_ifile(redir))
				return (ERROR_EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (error);
}
