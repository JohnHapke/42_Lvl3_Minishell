/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:53 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 14:22:47 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_remove_current_token(t_token **token_list, t_token *current)
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

void	ft_extract_variables(t_shell *shell, t_token **token_list)
{
	int		i;
	t_token	*current;
	char	*new_key;
	char	*new_value;

	i = 0;
	current = *token_list;
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD && ft_variable_check(current->value))
		{
			new_key = ft_substr(current->value, 0,
					(size_t)(ft_strchr(current->value, '=') - current->value));
			new_value = ft_substr(ft_strchr(current->value, '='), 1,
					ft_strlen(ft_strchr(current->value, '=')));
			ft_env_add_back(&shell->env_list,
				ft_env_new_node(new_key, ft_get_unquoted_str(new_value)));
			free(new_value);
			current = ft_remove_current_token(token_list, current);
		}
		else
			current = current->next;
	}
}

char	*ft_get_var_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		i++;
	}
	key = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	ft_expand_variables(t_shell *shell, char **value)
{
	int		i;
	char	*temp_str;
	char	*var_key;
	char	*var_value;
	bool	is_in_quote;

	i = 0;
	is_in_quote = false;
	while ((*value)[i] != '\0')
	{
		if ((*value)[i] == '\'')
			is_in_quote = !is_in_quote;
		if ((*value)[i] == '$' && is_in_quote == false)
		{
			var_key = ft_get_var_key(&(*value)[i + 1]);
			var_value = ft_compare_var_keys(var_key, shell->env_list);
			temp_str = ft_insert_str(*value, var_value,
					ft_strlen(var_key + 1), &i);
			free(var_key);
			free(*value);
			*value = temp_str;
		}
		i++;
	}
}

void	ft_expansion_handler(t_shell *shell, t_token **token_list)
{
	char	*temp;
	t_token	*current;

	ft_extract_variables(shell, token_list);
	current = *token_list;
	while (current)
	{
		ft_expand_variables(shell, &current->value);
		temp = current->value;
		current->value = ft_get_unquoted_str(current->value);
		free(temp);
		current = current->next;
	}
}
