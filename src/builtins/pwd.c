/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:26 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/10 22:37:31 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// implementation should be correct

int	ft_pwd(t_shell *shell, char **argv)
{
	char	*buffer;

	(void) shell;
	buffer = NULL;
	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (ft_other_error(E_OTHER, argv[0]));
	else
	{
		write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		write(STDOUT_FILENO, "\n", 1);
		free(buffer);
	}
	return (EXIT_SUCCESS);
}
