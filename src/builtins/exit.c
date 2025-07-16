/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:22 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:24:58 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	shell->should_exit = true;
	if (argv[1] && argv[2])
		return (ft_builtin_error(EXIT_FAILURE, "exit", NULL,
				"too many arguments"));
	if (argv[1])
	{
		if ((argv[1][i] == '-' || argv[1][i] == '+') && argv[1][i + 1])
			i++;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				return (ft_builtin_error(ERROR_USAGE, "exit", NULL,
						"numeric argument required"));
			i++;
		}
		return (ft_atoi(argv[1]) % 256);
	}
	else
		return (shell->exit_status);
}
