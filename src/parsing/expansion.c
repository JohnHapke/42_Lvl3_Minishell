/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:53 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/13 16:25:06 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
