/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/26 15:59:59 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../get_next_line/get_next_line.h"

static void	ft_close(void *data)
{
	int	*fd;

	fd = (int *)data;
	close(*fd);
}

void	ft_output_handler(t_redir *redir)
{
	int		*file_fd;
	t_list	*files;

	file_fd = NULL;
	files = NULL;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			file_fd = malloc(sizeof (int));
			if (!file_fd)
				ft_error_handler();
			if (redir->type == REDIR_OUT)
				*file_fd = open(redir->file,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (redir->type == REDIR_APPEND)
				*file_fd = open(redir->file,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			ft_lstadd_back(&files, ft_lstnew(file_fd));
		}
		redir = redir->next;
	}
	if (file_fd != NULL)
	{
		dup2(*file_fd, STDOUT_FILENO);
		ft_lstiter(files, &ft_close);
		ft_lstclear(&files, &free);
	}
}
