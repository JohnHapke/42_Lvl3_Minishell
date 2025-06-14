/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:53 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/14 15:34:22 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// function programmed by Igor -> implementation in next commit 
char	*ft_insert_str(char *str, char *insert, size_t where)
{
	char	*ret;

	if (where > (ft_strlen(str) + ft_strlen(str)))
	ret = ft_calloc(ft_strlen(str) + ft_strlen(insert), sizeof(char));
	ft_memcpy(ret, str, where);
	ft_memcpy(&ret[where], insert, ft_strlen(insert));
	ft_memcpy(&ret[ft_strlen(insert) + where], &str[where], ft_strlen(&str[where]));
	return (ret);
}

/*
1. extract the variables and save them into t_env within t_shell (add_back)
	-> f.e. name=user
2. delete the token in token_list
	-> delete token with char "name=user" 
3. search through token_list the token to expand
	-> find $ fill them with variable value
	-> ignore all single quoted strings 
4. delete quotes
*/

bool	ft_variable_check(char *value)
{
	int	i;

	i = -1;
	if (ft_strchr(value, '=') == NULL || ft_isdigit(value[0]))
		return (false);
	while (value[i++] != '=')
	{
		if (ft_isalnum(value[i]) && value[i] != '_')
			return (false);
	}
	i++;
	//rest is ignored
}

void	ft_extract_variables(t_shell *shell, t_token *token_list)
{
	while (token_list->next != NULL)
	{
		if (token_list->type == TOKEN_WORD && ft_variable_check(token_list->value))
		{
			//add variable to env
			//remove token from token_list
			//ft_env_node_add_back(&shell->env_list, ft_env_new_node(line[0], line[1]));
		}
		token_list = token_list->next;
	}
}

void	ft_expand_variables(t_shell *shell, t_token *token_list)
{}

void	ft_remove_quotes()
{}


void	ft_expansion_handler(t_shell *shell, t_token *token_list)
{
	ft_extract_variables(shell, token_list);
	ft_expand_variables(shell, token_list);
	ft_remove_quotes(token_list);
}
