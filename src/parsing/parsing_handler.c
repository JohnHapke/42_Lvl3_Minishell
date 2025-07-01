/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/01 14:45:55 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parsing_handler(t_shell *shell, char *line)
{
	t_token			*token_list;
	t_command		*command;
	int				error;

	command = NULL;
	token_list = NULL;
	ft_token_handler(shell, &token_list, line);
	if (ft_token_validator(token_list) == 2)
		return (ERROR_USAGE);
	if (ft_expansion_handler(shell, &token_list) != EXIT_SUCCESS)
		return (128);
	ft_command_handler(shell, token_list, &command);
	error = ft_execution_handler(shell, command);
	ft_command_lstclear(&command);
	ft_token_lstclear(&token_list);
	if (error != 0)
		return (error);
	return (EXIT_SUCCESS);
}
