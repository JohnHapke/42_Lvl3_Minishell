/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:16:41 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/27 10:59:18 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_redir	*ft_new_node_redir(char	*file, t_redir_type type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = file;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_redir_add_back(t_redir **list, t_redir *new_node)
{
	t_redir	*current;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

void	ft_command_add_back(t_command **command, t_command *new_node)
{
	t_command	*current;

	if (!*command)
	{
		*command = new_node;
		return ;
	}
	current = *command;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

void	ft_command_lstclear(t_command **lst)
{
	t_command	*cmd_temp;
	t_redir		*redir_temp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		cmd_temp = (*lst)->next;
		ft_free_all((*lst)->args);
		while ((*lst)->redirs)
		{
			redir_temp = (*lst)->redirs->next;
			free((*lst)->redirs->file);
			free((*lst)->redirs);
			(*lst)->redirs = redir_temp;
		}
		free(*lst);
		*lst = cmd_temp;
	}
	*lst = NULL;
}