/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:18 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/06 14:27:43 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*ft_new_node(char *key, char *value)
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

static void	ft_env_node_add_back(t_env **lst, t_env *new_node)
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

void	ft_init_shell(t_shell *shell, char **envp)
{

	int		i;
	t_env	*head;	
	t_env	*current;
	char	**line;

	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		line = ft_split(envp[i], '=');
		/*if (line == NULL) //				TODO: error and clean up
			//cleanup and error handling*/
		current = ft_new_node(line[0], line[1]);
		ft_env_node_add_back(&head, current);
		ft_free_all(line);
		i++;
	}
	shell->env_array = envp;
}
