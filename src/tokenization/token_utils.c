/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:55:12 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/18 15:24:16 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_token_new_node(char *value, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		ft_error_handler();
	new->type = type;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_token_add_back(t_token **token_list, t_token *new_node)
{
	t_token	*current;

	if (!(*token_list))
		*token_list = new_node;
	else
	{
		new_node->prev = current;
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
