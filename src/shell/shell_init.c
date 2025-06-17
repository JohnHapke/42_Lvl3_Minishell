/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:18 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/17 11:09:35 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_env_new_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		ft_error_handler();
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_env_add_back(t_env **lst, t_env *new_node)
{
	if (!(*lst))
		*lst = new_node;
	else
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new_node;
	}
}

void	ft_shell_init(t_shell *shell, char **envp)
{
	int		i;
	char	**line;

	i = 0;
	shell->env_list = NULL;
	while (envp[i] != NULL)
	{
		line = ft_split(envp[i], '=');
		if (!line)
			ft_error_handler();
		ft_env_add_back(&shell->env_list, ft_env_new_node(line[0], line[1]));
		free(line);
		i++;
	}
	shell->env_array = envp;
}
