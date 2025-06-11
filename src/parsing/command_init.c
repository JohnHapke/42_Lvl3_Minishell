/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:41 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/11 17:59:28 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

ft_command_handler(t_token *token_list, t_command *command)
{
	if (token_list->type == TOKEN_REDIR_IN)
	{
		command->redirs = ft_add_node_redir();
		token_list = token_list->next;
	}
		command->redirs = ft_add_node_redir();
	while(token_list->type != TOKEN_REDIR_OUT)
	{
		ft_add_back_command(&command, ft_new_node());
		token_list = token_list->next;
	}
	while (token_list->next != NULL)
	{
		fill data into command->redir;
		command->redir->next;
		token_list = token_list->next;
	}
}

/*
iterate through token_list
1. is it a redir or a command? -> add new node in related list
2. itarate through all commands and allocate information into command list
3. iterate until NULL and allocate all information into redir list 
-> command and redir lists are allocated and useful

grammar rules:

1. a command line can start with a command or a redirection -> something erlse? yes/no
2. between commands just can be pipes -> yes/no?
3. after a redirection has to be a file or in case of input the limiter/here_doc ? yes/no
4. after redirection out can just be other redirection out with outfile but no command -> yes/no 
5. ...*/

int	ft_count_arguments(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (token_list->type == TOKEN_WORD)
			count++;
		else if (token_list->type == TOKEN_REDIR_IN
			|| token_list->type == TOKEN_REDIR_OUT)
			token_list = token_list->next;
		else
			break ;
		token_list = token_list->next;
	}
	return (count);
}

t_command	*ft_init_command_list(t_token *token_list)
{
	t_command	*command;

	command = NULL;
	command->args = malloc((ft_count_arguments(token_list) + 1) * sizeof(char *));
	if (!command->args)
		ft_error_handler();
	while (token_list->type != TOKEN_PIPE || token_list->type != NULL)
	{
		if (token_list->type == TOKEN_WORD)
			*command->args = token_list->value;
		else if (token_list->type == TOKEN_REDIR_IN
			|| token_list->type == TOKEN_REDIR_OUT)
		{
			command->redirs->type = token_list->type; // 4 types of redirection -> fct needed to explicity put the type
			*command->redirs->file = token_list->next->value;
			token_list = token_list->next;
		}
			*command->redirs->type = token_list->value;
		else
			break ;
		token_list = token_list->next;
	}
}


char	**ft_get_command_args(t_token **token_list, t_command *command)
{
	int	i;

	i = 0;
	command->args = malloc((ft_count_arguments((*token_list)) + 1) * sizeof(char *));
	if (!command->args)
		ft_error_handler();
	while ((*token_list))
	{
		if ((*token_list)->type == TOKEN_WORD)
			command->args = token_list->;//ADD TO ARGS
		else if ((*token_list)->type == TOKEN_REDIR_IN
			|| (*token_list)->type == TOKEN_REDIR_OUT)
		{
			ft_redir_list_add_back(/*new node*/);
			(*token_list) = (*token_list)->next;
		}
		else
			break ;
		(*token_list) = (*token_list)->next;
	}
}

t_command	*ft_command_handler(t_token *token_list, t_command *command)
{
	while (token_list)
	{
		if (token_list->type == TOKEN_PIPE)
			token_list = token_list->next;
		else
		{
			//make new token.
			command->args = ft_get_command_args(&token_list, command);
		}
	}
}
