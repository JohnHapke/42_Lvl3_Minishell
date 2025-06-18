/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:17 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/18 14:17:17 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_get_token_type(char c)
{
	if (c == '<')
		return (TOKEN_REDIR_IN);
	else if (c == '>')
		return (TOKEN_REDIR_OUT);
	else if (c == '|')
		return (TOKEN_PIPE);
	else
		return (TOKEN_WORD);
}

static char	*ft_get_token_value(char *line, int *i,
				t_token_type token_type)
{
	bool	is_in_quote;
	int		token_len;
	char	*token_value;

	token_len = *i;
	is_in_quote = false;
	while (line[token_len] != '\0')
	{
		if (line[*i] == '"' || line[*i] == '\'')
			is_in_quote = !is_in_quote;
		token_len++;
		if ((line[token_len] == ' '
				|| ft_get_token_type(line[token_len]) != token_type)
			&& is_in_quote == false)
			break ;
	}
	token_value = ft_substr(line, *i, token_len - *i);
	*i = token_len;
	return (token_value);
}

void	ft_token_handler(t_shell *shell, char *line)
{
	int				i;
	t_token_type	token_type;
	t_token			*token_list;

	i = 0;
	token_list = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		else
		{
			token_type = ft_get_token_type(line[i]);
			ft_token_add_back(&token_list, ft_token_new_node
				(ft_get_token_value(line, &i, token_type), token_type));
		}
	}
	ft_parsing_handler(shell, token_list);
}
