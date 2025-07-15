/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:36:34 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/15 14:54:23 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ft_envsize(t_env *lst)
{
	t_env	*temp;
	size_t	len;

	temp = lst;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

char	**ft_list_to_strv(t_env *env)
{
	int		i;
	char	*temp1;
	char	*temp2;
	char	**strv;

	i = 0;
	if (!env)
		return (NULL);
	strv = malloc((ft_envsize(env) + 1) * sizeof(char *));
	if (!strv)
		return (NULL);
	while (env)
	{
		temp1 = ft_strjoin(env->key, "=");
		temp2 = ft_strjoin(temp1, env->value);
		strv[i] = temp2;
		free(temp1);
		i++;
		env = env->next;
	}
	strv[i] = NULL;
	return (strv);
}

void	ft_delnode(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	ft_extract_node(t_env **list, t_env *remove)
{
	t_env	*current;
	t_env	*prev;

	if (!list || !*list || !remove)
		return ;
	current = *list;
	prev = NULL;
	if (current == remove)
	{
		*list = current->next;
		ft_delnode(remove);
		return ;
	}
	while (current && current != remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	prev->next = current->next;
	ft_delnode(remove);
}

int	ft_builtin_error(int code, char *cmd, char *optional, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (optional)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(optional, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	return (code);
}
