/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/26 16:36:52 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

static void	ft_heredoc(char *delimiter)
{
	char	*line;
	int		heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
		ft_error_handler();
	while (1)
	{
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
	dup2(heredoc_fd[0], STDIN_FILENO);
	close(heredoc_fd[0]);
}

void	ft_input_handler(t_redir *redir)
{
	int		file_fd;
	t_redir	*valid_redir;

	valid_redir = NULL;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			valid_redir = redir;
		redir = redir->next;
	}
	if (valid_redir)
	{
		if (valid_redir->type == REDIR_HEREDOC)
		{
			//write(STDERR_FILENO, valid_redir->file, ft_strlen(valid_redir->file));
			ft_heredoc(valid_redir->file);
		}
		else
		{
			file_fd = open(valid_redir->file, O_RDONLY);
			if (file_fd == -1)
				ft_error_handler(/*file could not be found*/);
			else
			{
				dup2(file_fd, STDIN_FILENO);
				close(file_fd);
			}
		}
	}
}
