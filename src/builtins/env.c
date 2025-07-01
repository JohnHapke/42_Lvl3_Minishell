/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:05 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/01 15:56:03 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_shell *shell, char **argv)
{
	t_env	*current;

	if (argv[1] != NULL)
	{
		//return (ft_other_error(E_OTHER, argv[1]));
		printf("env: Invalid argument: %s", argv[1]);
		return (1);
	}
	current = shell->env_list;
	printf("minishell builtin!\n");
	while (current)
	{
		printf("%s%c%s\n", current->key, '=', current->value);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
