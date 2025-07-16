/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:32:40 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 08:27:00 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(void)
{
	char	*input;
	char	*temp;

	input = NULL;
	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
	{
		input = ft_get_next_line(STDIN_FILENO);
		if (input)
		{
			temp = ft_strtrim(input, "\n");
			if (!temp)
				ft_other_error(E_MEM, NULL);
			free(input);
			input = temp;
		}
	}
	return (input);
}

void	ft_shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = ft_read_input();
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
