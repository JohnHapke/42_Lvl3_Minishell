/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:53 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/27 11:53:49 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			var_value = ft_list_getenv(var_key, shell->env_list, shell->user_env_list);
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

	ft_var_extract_handler(shell, token_list);
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
