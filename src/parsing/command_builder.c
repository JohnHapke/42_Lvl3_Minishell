/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:41 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 08:26:30 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_type	ft_get_redir_type(char	*value)
{
	if (ft_strncmp("<", value, ft_strlen(value)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp("<<", value, ft_strlen(value)) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(">", value, ft_strlen(value)) == 0)
		return (REDIR_OUT);
	else
		return (REDIR_APPEND);
}

static void	ft_fill_command_node(t_shell *shell, t_token **token_list,
				t_command *command)
{
	int	i;

	i = -1;
	command->redirs = NULL;
	command->args = malloc((ft_count_arguments((*token_list)) + 1)
			* sizeof(char *));
	if (!command->args)
		ft_error_handler(ERROR_MEMORY_ALLOC, &shell->exit_status);
	while ((*token_list))
	{
		if ((*token_list)->type == TOKEN_WORD)
			command->args[++i] = ft_strdup((*token_list)->value);
		else if ((*token_list)->type == TOKEN_REDIR_IN
			|| (*token_list)->type == TOKEN_REDIR_OUT)
		{
			ft_redir_add_back(&command->redirs,
				ft_new_node_redir(ft_strdup((*token_list)->next->value),
					ft_get_redir_type((*token_list)->value)));
			(*token_list) = (*token_list)->next;
		}
		else
			break ;
		(*token_list) = (*token_list)->next;
	}
	command->args[i + 1] = NULL;
}

void	ft_command_handler(t_shell *shell, t_token *token_list,
			t_command **command)
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
				ft_error_handler(ERROR_MEMORY_ALLOC, &shell->exit_status);
			new_node->next = NULL;
			ft_fill_command_node(shell, &token_list, new_node);
			ft_command_add_back(command, new_node);
		}
	}
}
