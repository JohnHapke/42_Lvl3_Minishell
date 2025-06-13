/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/13 14:53:45 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parsing_handler(t_token *token_list)
{
	t_command	*command;
	t_env		*env;

	env = NULL;
	command = NULL;
	if (ft_check_token_grammar(token_list) == 1)
		ft_error_handler();
	ft_expansion_handler(); //TODO
	ft_command_handler(token_list, &command);
}
