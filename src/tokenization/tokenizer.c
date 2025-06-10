/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:17 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/10 14:31:12 by iherman-         ###   ########.fr       */
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

//* Parser will have to handle things like invalid redirection values, (">>>" or "<<<<<<<") and unclosed quotes
static char	*ft_get_token_val(char *line, int *i,
				t_token_type token_type)
{
	int		token_len;
	char	break_char;
	char	*token_val;

	break_char = ' ';
	if (line[*i] == '"' || line[*i] == '\'')
		break_char = line[*i];
	token_len = *i;
	while (line[token_len] != '\0')
	{
		token_len++;
		if (line[token_len] == break_char)
			break ;
		if (break_char == ' ' && ft_get_token_type(line[token_len]) != token_type)
			break ;
	}
	token_val = ft_substr(line, *i, token_len - *i);
	*i = token_len;
	return (token_val);
}

static void	ft_tokenize_input(char *line, t_token **token_list)
{
	int				i;
	t_token_type	tok_type;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		else
		{
			tok_type = ft_get_token_type(line[i]);
			ft_token_add_back(token_list, ft_token_new_node
						(ft_get_token_val(line, &i, tok_type), tok_type));
		}
	}
}

void	ft_token_handler(char *line)
{
	t_token	*token_list;

	ft_tokenize_input(line, &token_list);
	ft_parsing_handler(); //TODO
}
