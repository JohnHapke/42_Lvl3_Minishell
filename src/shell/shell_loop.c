/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:32:40 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/11 17:41:47 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			shell->exit_status = ft_parsing_handler(shell, line);
			line = NULL;
			if (shell->should_exit == true)
				break ;
		}
	}
	free(line);
}
