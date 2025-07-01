/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/01 14:43:59 by iherman-         ###   ########.fr       */
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
	if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
		ft_process_error(E_DUP2);
	close(heredoc_fd[0]);
	return (EXIT_SUCCESS);
}

static void	ft_find_valid_node(t_redir *redir, t_redir **valid_redir)
{
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			*valid_redir = redir;
		redir = redir->next;
	}
}

int	ft_input_handler(t_redir *redir)
{
	int		file_fd;
	t_redir	*valid_redir;

	valid_redir = NULL;
	ft_find_valid_node(redir, &valid_redir);
	if (valid_redir)
	{
		if (valid_redir->type == REDIR_HEREDOC)
		{
			if (ft_heredoc(valid_redir->file) == 1)
				return (ERROR_EXIT_FAILURE);
		}
		else
		{
			file_fd = open(valid_redir->file, O_RDONLY);
			if (file_fd == -1)
				return (ft_other_error(E_OPEN, valid_redir->file));
			else
			{
				if (dup2(file_fd, STDIN_FILENO) == -1)
					return (ft_process_error(E_DUP2));
				close(file_fd);
			}
		}
	}
	return (EXIT_SUCCESS);
}
