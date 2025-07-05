/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:35 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/05 18:53:59 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// behavior should be correct. pipe_fd is not needed because builtin just changes directories and gives no output.

int	ft_cd(t_shell *shell, char **argv, int *pipe_fd)
{
	char	*home;
	int		i;

	(void) pipe_fd;
	home = NULL;
	if (argv[1] != NULL && argv[2] != NULL)
		return (ft_other_error(E_OTHER, argv[0]));
	else if (argv[1] == NULL)
	{
		i = -1;
		while (shell->env_array[++i] != NULL)
		{
			if (ft_strncmp(shell->env_array[i], "HOME=", 5) == 0)
			{
				home = shell->env_array[i] + 5;
				break ;
			}
		}
		if (home == NULL)
		{
			ft_putstr_fd("minishell: HOME not set", 2);
			return (EXIT_FAILURE);
		}
		if (chdir(home) == -1)
			return (ft_other_error(E_OTHER, argv[0]));
	}
	else if (argv[1] != NULL)
	{
		if (chdir(argv[1]) == -1)
			return (ft_other_error(E_OTHER, argv[0]));
	}
	else
		return (EXIT_SUCCESS);
}
