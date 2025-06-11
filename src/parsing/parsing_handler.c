/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/11 17:10:39 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Todo in parser:
		Check whether the tokens are valid
			Token too long (">>>" is invalid for redirection tokens)
				Throw error

		Check for invalid token structure
			Check for recurring non-word tokens (Pipe to a pipe is invalid ...)
		
		Build a command structure out of tokens for later execution (maybe, no idea how, though.)

TODO:

grammar rules needed

Pipeline: Command | Command '|' Pipeline
Command:  Word [Args] [Redirections]
Args:     Word [Args]
Redirections: Redirect [Redirections]

		*/

void	ft_parsing_handler(t_token *token_list)
{
	t_command	*command;
	t_env		*env;

	env = NULL;
	if (ft_check_token_grammar(token_list) == 1)
		ft_error_handler();
	command = ft_init_command_list(token_list);
	//expand
}
