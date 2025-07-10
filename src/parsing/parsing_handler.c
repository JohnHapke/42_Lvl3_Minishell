/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/10 20:46:49 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_free_return(int exit_code,
				t_token *token_list, t_command *command_list)
{
	ft_command_lstclear(&command_list);
	ft_token_lstclear(&token_list);
	return (exit_code);
}

int	ft_parsing_handler(t_shell *shell, char *line)
{
	t_token			*token_list;
	t_command		*command_list;
	int				exit_status;

	command_list = NULL;
	token_list = NULL;
	ft_token_handler(shell, &token_list, line);
	free(line);
	if (ft_token_validator(token_list) == ERROR_USAGE)
		return (ft_free_return(ERROR_USAGE, token_list, command_list));
	if (ft_expansion_handler(shell, &token_list) != EXIT_SUCCESS)
		return (128);
	if (token_list == NULL)
		return (ft_free_return(EXIT_SUCCESS, token_list, command_list));
	ft_command_handler(shell, token_list, &command_list);
	ft_token_lstclear(&token_list);
	exit_status = ft_execution_handler(shell, &command_list);
	ft_command_lstclear(&command_list);
	return (exit_status);
}
