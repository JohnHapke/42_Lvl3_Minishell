/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 17:08:58 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

void	ft_output_handler(t_redir *redir)
{
	int		file_fd;
	char	*line;

	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (redir->type == REDIR_OUT)
				file_fd = open(redir->file,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redir->type == REDIR_APPEND)
				file_fd = open(redir->file,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			while (1)
			{
				line = ft_get_next_line(STDIN_FILENO);
				if (!line)
					break ;
				write(file_fd, line, ft_strlen(line));
				free (line);
			}
			close(file_fd);
		}
	}
}
