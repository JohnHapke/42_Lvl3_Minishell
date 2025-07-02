/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:27:53 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/02 17:47:24 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*ft_remove_current_token(t_token **token_list, t_token *current)
{
	t_token	*temp;

	if (current == NULL)
		return (NULL);
	temp = current->next;
	if (current->prev)
		current->prev->next = current->next;
	else
		*token_list = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free(current->value);
	free(current);
	return (temp);
}

static t_env	*ft_find_env_node(char *var_key, t_env *env_list, t_env *user_env_list)
{
	while (env_list)
	{
		if (ft_strlen(env_list->key) == ft_strlen(var_key)
			&& (ft_strncmp(var_key, env_list->key, ft_strlen(var_key)) == 0))
			return (env_list);
		env_list = env_list->next;
	}
	while (user_env_list)
	{
		if (ft_strlen(user_env_list->key) == ft_strlen(var_key)
			&& (ft_strncmp(var_key, user_env_list->key, ft_strlen(var_key)) == 0))
			return (user_env_list);
		user_env_list = user_env_list->next;
	}
	return (NULL);
}

static void	ft_extract_variable(t_shell *shell, char *token_value)
{
	char	*new_key;
	char	*new_value;
	t_env	*found_variable;

	new_key = ft_substr(token_value, 0,
			(size_t)(ft_strchr(token_value, '=') - token_value));
	new_value = ft_substr(ft_strchr(token_value, '='), 1,
				ft_strlen(ft_strchr(token_value, '=')));
	found_variable = ft_find_env_node(new_key, shell->env_list, shell->user_env_list);
	if (found_variable)
	{
		free(found_variable->value);
		found_variable->value = ft_get_unquoted_str(new_value);
	}
	else
	{
		ft_env_add_back(&shell->user_env_list,
			ft_env_new_node(new_key, ft_get_unquoted_str(new_value)));
	}
	free(new_value);
}

void	ft_var_extract_handler(t_shell *shell, t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD && ft_variable_check(current->value))
		{
			ft_extract_variable(shell, current->value);
			current = ft_remove_current_token(token_list, current);
		}
		else
			current = current->next;
	}
}
