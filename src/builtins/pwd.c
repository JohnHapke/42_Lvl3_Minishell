/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:26 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/05 18:53:28 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implementation not working with pipes -> output should be in an outfile in case of "pwd | cat -e > outfile"

int	ft_pwd(t_shell *shell, char **argv, int *pipe_fd)
{
	char	*buffer;

	(void) shell;
	buffer = NULL;
	if (argv[1] != NULL)
		return (EXIT_FAILURE);
	else if (argv[1] == NULL)
	{
		buffer = getcwd(NULL, 0);
		if (!buffer)
			return (ft_other_error(E_OTHER, argv[0]));
		else
		{
			write(*pipe_fd, buffer, ft_strlen(buffer));
			write(*pipe_fd, "\n", 1);
			free(buffer);
		}
	}
	return (EXIT_SUCCESS);
}
