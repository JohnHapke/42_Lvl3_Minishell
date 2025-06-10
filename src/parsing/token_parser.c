/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/10 13:31:43 by iherman-         ###   ########.fr       */
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
*/

void	token_parser()
{
	
}