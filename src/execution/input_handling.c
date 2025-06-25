/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/25 17:00:28 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

static void	ft_input_redirection(char *filename, int *pipe_fd, t_redir_type type)
{
	char	*line;
	int		file_fd;

	if (type == REDIR_IN)
		file_fd = open(filename, O_RDONLY);
	else
		file_fd = STDIN_FILENO;
	while (1)
	{
		line = ft_get_next_line(file_fd);
		printf("input line: %s\n", line);
		if (!line)
			break ;
		if (type == REDIR_HEREDOC
			&& (ft_strncmp(line, filename, ft_strlen(filename)) == 0
			&& ft_strlen(line) - 1 == ft_strlen(filename)))
		{
			free (line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free (line);
	}
	close(file_fd);
}

void	ft_input_handler(t_redir *redir)
{
	int		pipe_fd[2];
	t_redir	*valid_redir;

	if (pipe(pipe_fd) == -1)
		ft_error_handler();
	valid_redir = NULL;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			valid_redir = redir;
		redir = redir->next;
	}
	if (valid_redir)
	{
		ft_input_redirection(valid_redir->file, pipe_fd, valid_redir->type);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
