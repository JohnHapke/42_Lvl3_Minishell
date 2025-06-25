/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:32:40 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/25 15:41:03 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL)
			break ;
		ft_token_handler(shell, line);
		// TODO
		add_history(line);
		free(line);
	}
}
