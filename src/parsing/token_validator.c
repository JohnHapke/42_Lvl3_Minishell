/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:44:47 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 08:26:52 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_validation_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (ERROR_USAGE);
}

static int	ft_redirection_check(t_token *token)
{
	size_t	token_len;

	if (token->value == NULL)
		return (ft_validation_error("token not found"));
	token_len = ft_strlen(token->value);
	if (!token_len)
		return (ft_validation_error("token not found"));
	if (token->next->type != TOKEN_WORD)
		return (ft_validation_error(token->next->value));
	return (EXIT_SUCCESS);
}

static int	ft_pipe_check(t_token *token)
{
	size_t	token_len;

	if (token->value == NULL)
		return (ft_validation_error("token not found"));
	token_len = ft_strlen(token->value);
	if (!token_len)
		return (ft_validation_error("token not found"));
	if (ft_strncmp(token->value, "|", token_len) != 0)
		return (ft_validation_error(token->value));
	if (token->next->type == TOKEN_PIPE)
		return (ft_validation_error("|"));
	if (token->prev == NULL || token->prev->type != TOKEN_WORD)
		return (ft_validation_error("|"));
	return (EXIT_SUCCESS);
}

int	ft_token_validator(t_token *token_list)
{
	if (token_list == NULL)
		return (EXIT_SUCCESS);
	while (token_list->next != NULL)
	{
		if ((token_list->type == TOKEN_REDIR_IN
				|| token_list->type == TOKEN_REDIR_OUT))
		{
			if (ft_redirection_check(token_list) == ERROR_USAGE)
				return (ERROR_USAGE);
		}
		if (token_list->type == TOKEN_PIPE)
		{
			if (ft_pipe_check(token_list) == ERROR_USAGE)
				return (ERROR_USAGE);
		}
		token_list = token_list->next;
	}
	if (token_list->type != TOKEN_WORD)
		return (ft_validation_error("newline"));
	return (EXIT_SUCCESS);
}
