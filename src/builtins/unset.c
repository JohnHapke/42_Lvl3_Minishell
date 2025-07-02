/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:29 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/02 17:40:08 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_shell *shell, char **argv, int *pipe_fd)
{
	t_env	*current;

	current = shell->env_list;
	if (current == NULL)
		return (EXIT_SUCCESS);
	while (current)
	{
		if (ft_strncmp(current->key, argv[1], ft_strlen(current->key)) == 0)
		{
			if (current = shell->env_list)
			{
				shell->env_list = shell->env_list->next;
				free(current->key);
				free(current->value);
				free(current);
				
			}
		}
	}
	while (current)
	{
		
	}
	return (EXIT_SUCCESS);
}