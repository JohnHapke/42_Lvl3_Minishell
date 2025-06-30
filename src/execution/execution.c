/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:02:02 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/30 15:09:23 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_getenv(char **env)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

static char	*ft_get_cmd_path(char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*sub_path;
	char	*cmd_path;

	path = ft_getenv(env);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		sub_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(sub_path, cmd);
		free(sub_path);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free(path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free(path);
	return (NULL);
}

void	ft_execution(char **args, char **env)
{
	char	*cmd_path;

	if (!args || !args[0])
	{
		ft_command_error(E_CMD, args[0]);
		exit(127);
	}
	cmd_path = ft_get_cmd_path(args[0], env);
	if (!cmd_path)
	{
		ft_command_error(E_CMD, args[0]);
		exit(127);
	}
	execve(cmd_path, args, env);
	free(cmd_path);
	if (errno == EACCES)
	{
		ft_command_error(E_PERMISSION, args[0]);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		ft_command_error(E_CMD, args[0]);
		exit(127);
	}
	else
	{
		ft_other_error(E_OTHER, args[0]);
		exit(1);
	}
}
