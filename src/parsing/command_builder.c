/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:41 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/12 15:59:21 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir_type	ft_get_redir_type(char	*value)
{
	if (ft_strncmp("<", value, ft_strlen(value)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp("<<", value, ft_strlen(value)) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(">", value, ft_strlen(value)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(">>", value, ft_strlen(value)) == 0)
		return (REDIR_APPEND);
	else
		ft_error_handler();
}

void	ft_fill_command_node(t_token **token_list, t_command *command)
{
	int	i;

	i = 0;
	command->redirs = NULL;
	command->args = malloc((ft_count_arguments((*token_list)) + 1)
			* sizeof(char *));
	if (!command->args)
		ft_error_handler();
	while ((*token_list))
	{
		if ((*token_list)->type == TOKEN_WORD)
			command->args[i++] = (*token_list)->value;
		else if ((*token_list)->type == TOKEN_REDIR_IN
			|| (*token_list)->type == TOKEN_REDIR_OUT)
		{
			ft_redir_add_back(&command->redirs,
				ft_new_node_redir((*token_list)->value,
					ft_get_redir_type((*token_list)->value)));
			(*token_list) = (*token_list)->next;
		}
		else
			break ;
		(*token_list) = (*token_list)->next;
	}
}

void	ft_command_handler(t_token *token_list, t_command **command)
{
	t_command	*new_node;

	while (token_list)
	{
		if (token_list->type == TOKEN_PIPE)
			token_list = token_list->next;
		else
		{
			new_node = malloc(sizeof(t_command));
			if (!new_node)
				return (NULL);
			ft_fill_command_node(&token_list, new_node);
			ft_command_add_back(command, new_node);
		}
	}
}
