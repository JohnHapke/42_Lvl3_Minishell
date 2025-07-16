/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:26 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 14:10:57 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s\n", buffer);
		free(buffer);
	}
	return (EXIT_SUCCESS);
}
