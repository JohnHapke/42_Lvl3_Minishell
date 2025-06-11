/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/10 16:26:27 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Todo in parser:
		Check whether the tokens are valid
			Token too long (">>>" is invalid for redirection tokens)
				Throw error

		Check for invalid token structure
			Check for recurring non-word tokens (Pipe to a pipe is invalid ...)
		
		Build a command structure out of tokens for later execution (maybe, no idea how, though.)
*/

void	ft_parsing_handler(t_token *token_list)
{
	t_redir		*redir;
	t_command	*command;
	t_env		*env;

	redir = NULL;
	command = NULL;
	env = NULL;
	if (ft_check_token() == 1)
		ft_error_handler();
}

int	ft_check_token(t_token *token_list)
{
	t_token	*prev;
	size_t	token_len;

	prev = NULL;
	while(token_list->next != NULL)
	{
		token_len = ft_strlen(token_list->value);
		if (!token_len)
			return (1);
		if ((token_list->type == TOKEN_REDIR_IN || token_list->type == TOKEN_REDIR_OUT) && (token_len > 2
			|| token_list->next->type != TOKEN_WORD))
			return (1);
		if (token_list->type == TOKEN_PIPE && (ft_strncmp(token_list->value, "|", ft_strlen(token_list->value) != 0)
			|| (token_list->next->type != TOKEN_WORD && (prev == NULL || prev->type != TOKEN_WORD))))
			return (1);
		prev = token_list;
		token_list = token_list->next;
	}
	if (token_list->type != TOKEN_WORD)
		return (1);
	return (0);
}
/*

< << -> need a word after 
> >> -> need a word after 
| -> need a word before and after

*/
