/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:47 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/30 14:48:19 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_token_validator(t_token *token_list)
{
	size_t	token_len;

	while (token_list->next != NULL)
	{
		token_len = ft_strlen(token_list->value);
		if (!token_len)
			return (2);
		if ((token_list->type == TOKEN_REDIR_IN
				|| token_list->type == TOKEN_REDIR_OUT) && (token_len > 2
				|| token_list->next->type != TOKEN_WORD))
			return (2);
		if (token_list->type == TOKEN_PIPE && (ft_strncmp(token_list->value,
					"|", token_len != 0)
				|| (token_list->next->type != TOKEN_WORD
					&& (token_list->prev == NULL
						|| token_list->prev->type != TOKEN_WORD))))
			return (2);
		token_list = token_list->next;
	}
	if (token_list->type != TOKEN_WORD)
		return (1);
	return (0);
}
