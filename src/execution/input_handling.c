/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:42:15 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/10 17:56:21 by iherman-         ###   ########.fr       */
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

static void	ft_get_ifile(t_list **files, t_redir *redir, int *file_fd)
{
	if (redir->type == REDIR_HEREDOC)
		*file_fd = ft_heredoc(redir->file);
	else if (redir->type == REDIR_IN && access(redir->file, R_OK) == 0)
		*file_fd = open(redir->file, O_RDONLY);
	else
		*file_fd = -1;
	if (*file_fd < 0)
	{
		write(2, "minishell$ ", 12);
		write(2, redir->file, ft_strlen(redir->file));
		write(2, ": No such file or directory\n", 29);
	}
	ft_lstadd_back(files, ft_lstnew(file_fd));
}

int	ft_iofile_error_return(t_list **files, int error, char *arg)
{
	int		return_value;
	int		*temp_content;
	t_list	*current;
	
	return_value = EXIT_SUCCESS;
	current = *files;
	while (current)
	{
		temp_content = (current->content);
		if (*temp_content < 0)
			return_value = E_OPEN;
		current = current->next;
	}
	ft_lstiter(*files, &ft_list_close);
	ft_lstclear(files, &free);
	if (error != EXIT_SUCCESS)
		return (ft_other_error(error, arg));
	return (return_value);
}

int	ft_input_handler(t_redir *redir)
{
	t_list	*files;
	int		*file_fd;
	char	*last_filename;
	
	file_fd = NULL;
	files = NULL;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC || redir->type == REDIR_IN)
		{
			file_fd = malloc(sizeof (int));
			if (!file_fd)
				return (ft_iofile_error_return(&files, E_MEM, NULL));
			ft_get_ifile(&files, redir, file_fd);
			last_filename = redir->file;
		}
		redir = redir->next;
	}
	if (file_fd != NULL)
	{
		if (*file_fd > 0 && dup2(*file_fd, STDIN_FILENO) == -1)
			return (ft_iofile_error_return(&files, E_DUP2, last_filename));
		return (ft_iofile_error_return(&files, EXIT_SUCCESS, NULL));
	}
	return (EXIT_SUCCESS);
}
