/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:21:21 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 17:00:37 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*void	ft_error_handler(int i, char *argv)
{
	if (i == 1)
	{
		ft_putstr_fd("./pipex: ", 2);
		perror(argv);
	}
	else if (i == 2)
	{
		perror("pipe");
		exit(1);
	}
	else if (i == 3)
	{
		perror("fork");
		exit(1);
	}
	else if (i == 4)
	{
		ft_putstr_fd("./pipex: command not found: ", 2);
		ft_putstr_fd(argv, 2);
		write(2, "\n", 1);
	}
}*/

void	ft_free(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}
