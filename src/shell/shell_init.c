/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:18 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 14:21:14 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
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

int	ft_init_environment(t_shell *shell, char **envp)
{
	char	*new_key;
	char	*new_value;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		new_key = ft_substr(envp[i], 0,
				(size_t)(ft_strchr(envp[i], '=') - envp[i]));
		new_value = ft_substr(ft_strchr(envp[i], '='), 1,
				ft_strlen(ft_strchr(envp[i], '=')));
		ft_env_add_back(&shell->env_list, ft_env_new_node(new_key, new_value));
		i++;
	}
	shell->env_array = malloc((i + 1) * sizeof(char *));
	if (!shell->env_array)
		return (ft_other_error(E_MEM, NULL));
	i = 0;
	while (envp[i])
	{
		shell->env_array[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->env_array[i] = NULL;
	return (0);
}

void	ft_shell_init(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->user_env_list = NULL;
	shell->exit_status = 0;
	shell->should_exit = false;
	ft_init_environment(shell, envp);
}
