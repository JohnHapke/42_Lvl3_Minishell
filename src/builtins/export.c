/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:24 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/10 22:37:17 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Only used when variable key is invalid: e.g. "//varkey" is invalid due to characters */
static int	ft_export_error_message(char *identifier)
{
	ft_putstr_fd("Export: ", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd(": is not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	char	new_env;
	t_env	*node;

	i = 1;
	while (argv[i])
	{
		if (node)
		{
		}
		else
			return (EXIT_FAILURE);
		i++;
	}
	new_env = ft_list_to_strv(shell->env_list);
	return (EXIT_SUCCESS);
}
