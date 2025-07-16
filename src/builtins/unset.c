/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:29 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:25:07 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_remove_key(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = shell->env_list;
	while (current)
	{
		if (ft_strlen(key) == ft_strlen(current->key)
			&& ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			free(current->key);
			free(current->value);
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = shell->env_list->next;
			free(current);
			return (true);
		}
		prev = current;
		current = current->next;
	}
	return (false);
}

int	ft_unset(t_shell *shell, char **argv)
{
	char	**new_env;
	int		i;
	bool	realloc;

	(void) argv;
	i = 1;
	realloc = false;
	while (argv[i])
	{
		if (ft_remove_key(shell, argv[1]) == true)
			realloc = true;
		i++;
	}
	if (realloc)
	{
		ft_free_all(shell->env_array);
		new_env = ft_list_to_strv(shell->env_list);
		shell->env_array = new_env;
	}
	return (EXIT_SUCCESS);
}
