/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:45:17 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/06 16:18:58 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	example of tokens
//		Input: < infile cmd1 | cmd2 > outfile

t_token	*ft_new_node_token(t_token_type type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);	
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_back_node_token(t_token **token_list, t_token *new_node)
{
	if (!(*token_list))
		*token_list = new_node;
	else
	{
		while ((*token_list)->next != NULL)
			*token_list = (*token_list)->next;
		(*token_list)->next = new_node;
	}
}

t_token	*ft_token_operator(t_token_type type, char *line, int *i)
{
	t_token	*current;
	char	token_val[3];

	token_val[0] = line[*i];
	token_val[1] = '\0';
	if (line[*i + 1] == line[*i])	
	{
		token_val[1] = line[*i];
		token_val[2] = '\0';
		i++;
	}
	current = ft_new_node_token(type, ft_strdup(token_val));
	return (current);
}

char	*ft_get_word_token(char *line, int *i)
{
	char	*word;
	int		start;

	start = i;
	while (line[*i] != 32 || line[*i] != '<'
			|| line[*i] != '>' || line[*i] != '\0' || line[*i] != '|')
		*i++;
	word = ft_substr(line, start, i);
	*i--;
}

void	ft_tokenization(char *line, t_token *token_list)
{
	int		i;
	t_token	*current;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 32)
			i++;
		else if (line[i] == '<')
			current = ft_token_operator(TOKEN_REDIR_IN, line, &i);
		else if (line[i] == '>')
			current = ft_token_operator(TOKEN_REDIR_OUT, line, &i);
		else if (line[i] == '|')
			current = ft_token_operator(TOKEN_PIPE, line, &i);
		else
			current = ft_new_node_token(TOKEN_WORD, ft_get_word_token(line, &i));
		ft_add_back_node_token(&token_list, current);
		i++;
	}
}

void	ft_token_handler(char *line)
{
	t_token	*token_list;

	token_list = malloc(sizeof(t_token));
	if (!token_list)
		return (NULL);
	ft_tokenization(line, token_list);
	ft_parsing_handler(); //TODO
}
