/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:17 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/04 16:27:18 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token_type	ft_get_token_type(char c)
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

static size_t	ft_token_word_len(char *line)
{
	size_t	token_len;
	bool	in_single_quote;
	bool	in_double_quote;

	token_len = 0;
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
				|| ft_get_token_type(line[token_len]) != TOKEN_WORD))
			break ;
		token_len++;
	}
	return (token_len);
}

static char	*ft_get_token_value(char *line, size_t *i,
				t_token_type token_type)
{
	size_t	token_len;
	char	*token_value;

	token_len = *i;
	if (token_type == TOKEN_WORD)
		token_len += ft_token_word_len(&line[*i]);
	else
	{
		if (ft_get_token_type(line[token_len]) == token_type)
			token_len++;
		if (ft_get_token_type(line[token_len]) == token_type
			&& (token_type == TOKEN_REDIR_IN || token_type == TOKEN_REDIR_OUT))
			token_len++;
	}
	token_value = ft_substr(line, *i, token_len - *i);
	*i = token_len;
	return (token_value);
}

void	ft_token_handler(t_shell *shell, t_token **token_list, char *line)
{
	size_t			i;
	t_token_type	token_type;
	t_token			*new_node;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			token_type = ft_get_token_type(line[i]);
			new_node = ft_token_new_node(ft_get_token_value(line, &i, token_type), token_type);
			if (!new_node)
				ft_error_handler(ERROR_MEMORY_ALLOC, &shell->exit_status);
			ft_token_add_back(token_list, new_node);
		}
	}
}
