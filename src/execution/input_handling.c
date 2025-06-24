/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 17:09:30 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

static void	ft_input_redirection(char *file, int *fd, t_redir_type type)
{
	char	*line;
	int		file_fd;

	if (type == REDIR_IN)
		file_fd = open(file, O_RDONLY);
	else
		file_fd = STDIN_FILENO;
	if (pipe(fd) == -1)
		ft_error_handler();
	while (1)
	{
		line = ft_get_next_line(file_fd);
		if (!line)
			break ;
		if (type == REDIR_HEREDOC
			&& (ft_strncmp(line, file, ft_strlen(file)) == 0
			&& ft_strlen(line) - 1 == ft_strlen(file)))
		{
			free (line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free (line);
	}
	close(file_fd);
}

void	ft_input_handler(t_redir *redir)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_error_handler();
	while (redir)
	{
		ft_input_redirection(redir->file, fd, redir->type);
		redir = redir->next;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
