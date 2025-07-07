/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:24 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/07 15:40:41 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_export_error_message(char *identifier, int fd)
{
	ft_putstr_fd("Export: ", fd);
	ft_putstr_fd(identifier, fd);
	ft_putstr_fd(": is not a valid identifier", fd);
	return (EXIT_FAILURE);
}



static t_env	*ft_create_env_node(t_shell *shell, char *arg, int pipe_fd)
{
	t_env	*node;
	char	*new_key;
	char	*new_value;
	int		i;

	i = 0;
	node = (t_env *)malloc(sizeof (t_env));
	if (!node)
		return (NULL);

	free(new_key);
	free(new_value);
	return (node);
}

static void	ft_export_variable(t_shell *shell, t_env *node, char *arg)
{
	t_env	*found_node;

	if (!(node->value))
	{	//This check is to see whether the node has a value assignation
			// if it doesn't, look through the user_env_list to find a corresponding node, remove it from user_env_list and add it to environment.
	
	}
	else
	{	// If it does, look through both lists to find a variable to replace
	
		
	}
}

int	ft_export(t_shell *shell, char **argv, int *pipe_fd)
{
	int		i;
	char	new_env;
	t_env	*node;

	i = 1;
	while (argv[i])
	{
		if (node)
		{
			ft_create_env_node(shell, argv[i], pipe_fd[1]);
			ft_export_variable(shell, node, argv[1]);
		}
		else
			return (EXIT_FAILURE);
		i++;
	}
	new_env = ft_list_to_strv(shell->env_list);
	return (EXIT_SUCCESS);
}
