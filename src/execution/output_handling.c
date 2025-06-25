/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/25 17:06:48 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

void	ft_output_handler(t_redir *redir)
{
	int		file_fd;
	char	*line;
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
		if (valid_redir->type == REDIR_OUT)
			file_fd = open(valid_redir->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (valid_redir->type == REDIR_APPEND)
			file_fd = open(valid_redir->file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		while (1)
		{
			line = ft_get_next_line(STDIN_FILENO);
			printf("output line: %s\n", line);
			if (!line)
				break ;
			write(file_fd, line, ft_strlen(line));
			free (line);
		}
		close(file_fd);
	}
}
