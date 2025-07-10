/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:49:22 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/10 17:51:35 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_list_close(void *data)
{
	int	*fd;

	fd = (int *)data;
	if (fd > 0)
		close(*fd);
}

static void	ft_get_ofile(t_list **files, t_redir *redir, int *file_fd)
{
	if (access(redir->file, W_OK) != 0)
	{
		*file_fd = -1;
		ft_other_error(E_ACCESS, redir->file);
	}
	else if (redir->type == REDIR_OUT)
		*file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		*file_fd = open(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_lstadd_back(files, ft_lstnew(file_fd));
}

int	ft_output_handler(t_redir *redir, int out)
{
	int		*file_fd;
	t_list	*files;
	char	*last_filename;

	file_fd = NULL;
	files = NULL;
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			file_fd = malloc(sizeof (int));
			if (!file_fd)
				return (ft_iofile_error_return(&files, E_MEM, NULL));
			ft_get_ofile(&files, redir, file_fd);
			last_filename = redir->file;
		}
		redir = redir->next;
	}
	if (file_fd != NULL)
	{
		if (*file_fd > 0 && dup2(*file_fd, out) == -1)
			return (ft_iofile_error_return(&files, E_DUP2, last_filename));
		return (ft_iofile_error_return(&files, EXIT_SUCCESS, NULL));
	}
	return (EXIT_SUCCESS);
}
