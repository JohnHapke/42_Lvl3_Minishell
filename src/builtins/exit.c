/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:22 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/11 13:45:46 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	shell->should_exit = true;
	if (argv[1])
	{
		while (argv[1][i])
		{
			if (!(ft_isdigit(argv[1][i])))
			{
				write(2, "minishell: exit: ", 18);
				write(2, argv[i], ft_strlen(argv[i]));
				write(2,  "numeric argument required\n", 27);
				return (ERROR_USAGE);
			}
			i++;
		}
		return (ft_atoi(argv[1]) % 256);
	}
	else
		return (shell->exit_status);
}
