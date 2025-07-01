/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:46:38 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/01 16:37:58 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_builtin_handler(t_shell *shell, char **args)
{
	if (ft_strlen(args[0]) && ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (ft_echo(args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (ft_cd(args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (ft_pwd(args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (ft_export(shell, args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (ft_unset(args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (ft_env(shell, args));
	else if (ft_strlen(args[0]) && ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (ft_exit(args));
	return (EXIT_SUCCESS);
}
