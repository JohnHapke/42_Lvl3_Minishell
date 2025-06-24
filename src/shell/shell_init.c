/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:18 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/24 17:15:17 by jhapke           ###   ########.fr       */
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
	t_env	*current;

	current = *lst;
	if (!(*lst))
		*lst = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_shell_init(t_shell *shell, char **envp)
{
	int		i;
	char	*new_key;
	char	*new_value;

	i = 0;
	shell->env_list = NULL;
	while (envp[i] != NULL)
	{
		new_key = ft_substr(envp[i], 0,
				(size_t)(ft_strchr(envp[i], '=') - envp[i]));
		new_value = ft_substr(ft_strchr(envp[i], '='), 1,
				ft_strlen(ft_strchr(envp[i], '=')));
		ft_env_add_back(&shell->env_list, ft_env_new_node(new_key, new_value));
		i++;
	}
	shell->env_array = malloc((i + 1) * sizeof(char));
	i = 0;
	while (envp[i])
	{
		shell->env_array[i] = ft_strdup(envp[i]);
		printf("%s\n", shell->env_array[i]);
		i++;
	}
	shell->env_array[i] = NULL;
}
