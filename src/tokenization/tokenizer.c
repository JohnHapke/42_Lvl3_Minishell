/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:17 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/24 14:21:38 by iherman-         ###   ########.fr       */
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
	bool	in_single_quote;
	bool	in_double_quote;
	int		token_len;
	char	*token_value;

	token_len = *i;
	in_single_quote = false;
	in_double_quote = false;
	while (line[token_len] != '\0')
	{
		if (line[token_len] == '\"' && in_single_quote == false)
			in_double_quote = !in_double_quote;
		if (line[token_len] == '\'' && in_double_quote == false)
			in_single_quote = !in_single_quote;
		if ((!in_single_quote && !in_double_quote)
			&& (line[token_len] == ' '
				|| ft_get_token_type(line[token_len]) != token_type))
			break ;
		token_len++;
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
