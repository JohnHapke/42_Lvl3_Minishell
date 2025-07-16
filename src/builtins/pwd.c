/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:26 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:25:05 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
