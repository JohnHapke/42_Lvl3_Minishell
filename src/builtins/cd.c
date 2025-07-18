/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:35 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:24:46 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *shell, char **argv)
{
	char	*home;
	int		i;

	home = NULL;
	if (argv[1] != NULL && argv[2] != NULL)
		return (ft_builtin_error(1, "cd", NULL, "too many arguments"));
	else if (argv[1] == NULL)
	{
		i = -1;
		while (shell->env_array[++i] != NULL && home == NULL)
		{
			if (ft_strncmp(shell->env_array[i], "HOME=", 5) == 0)
				home = shell->env_array[i] + 5;
		}
		if (home == NULL)
			return (ft_builtin_error(1, "cd", NULL, "HOME not set"));
		if (chdir(home) == -1)
			return (ft_other_error(E_OTHER, argv[0]));
	}
	else if (argv[1] != NULL)
	{
		if (chdir(argv[1]) == -1)
			return (ft_other_error(E_OTHER, "cd"));
	}
	return (EXIT_SUCCESS);
}
