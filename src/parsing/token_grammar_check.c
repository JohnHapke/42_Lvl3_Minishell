/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_grammar_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:47 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/11 15:46:46 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_token_grammar(t_token *token_list)
{
	t_token	*prev;
	size_t	token_len;

	prev = NULL;
	while (token_list->next != NULL)
	{
		token_len = ft_strlen(token_list->value);
		if (!token_len)
			return (1);
		if ((token_list->type == TOKEN_REDIR_IN
				|| token_list->type == TOKEN_REDIR_OUT) && (token_len > 2
				|| token_list->next->type != TOKEN_WORD))
			return (1);
		if (token_list->type == TOKEN_PIPE && (ft_strncmp(token_list->value,
					"|", ft_strlen(token_list->value) != 0)
				|| (token_list->next->type != TOKEN_WORD
					&& (prev == NULL || prev->type != TOKEN_WORD))))
			return (1);
		prev = token_list;
		token_list = token_list->next;
	}
	if (token_list->type != TOKEN_WORD)
		return (1);
	return (0);
}
