/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:26 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/07 08:22:06 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implementation should be correct

int	ft_pwd(t_shell *shell, char **argv, int *pipe_fd)
{
	char	*buffer;

	(void) shell;
	buffer = NULL;
	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (ft_other_error(E_OTHER, argv[0]));
	else
	{
		write(pipe_fd[1], buffer, ft_strlen(buffer));
		write(pipe_fd[1], "\n", 1);
		free(buffer);
	}
	return (EXIT_SUCCESS);
}
