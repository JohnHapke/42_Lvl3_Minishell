/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:45:28 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/11 16:55:09 by iherman-         ###   ########.fr       */
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

static char	*ft_get_command(char *cmd, char **env)
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

char	*ft_get_cmd_path(char *cmd, char **env)
{
	char	*path;

	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		path = ft_get_relative_cmd_path(cmd);
	else if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	else
		path = ft_get_command(cmd, env);
	return (path);
}
