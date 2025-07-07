/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:45:28 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/07 16:37:01 by iherman-         ###   ########.fr       */
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

static char	*ft_get_relative_path(char **paths, int *i)
{
	char	*path;
	char	*path_temp;
	char	*starting_dir;

	*i = 0;
	starting_dir = getcwd(NULL, 0);
	while (paths[*i])
	{
		chdir(paths[*i]);
		*i++;
	}
	path_temp = getcwd(NULL, 0);
	path = ft_strjoin(path_temp, "/");
	free(path_temp);
	chdir(starting_dir);
	free(starting_dir);
	return (path);
}

static char	*ft_get_relative_command(char *cmd)
{
	char	**paths;
	char	*sub_path;
	char	*cmd_path;
	int		i;

	paths = ft_split(cmd, '/');
	sub_path = ft_get_relative_path(paths, &i);
	cmd_path = ft_strjoin(sub_path, paths[i - 1]);
	ft_free(paths);
	free(sub_path);
	printf("%s\n", cmd_path);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	else
	{
		free(cmd_path);
		return (NULL);
	}
}

char	*ft_get_cmd_path(char *cmd, char **env)
{
	char	*path;

	if (ft_strncmp(cmd, "./", 2) == 0) //* relative path (could also be ../, need to fix later)
		path = ft_get_relative_command(cmd);
	else if (cmd[0] == '/') //* absolute path
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	else //* PATH variable
		path = ft_get_command(cmd, env);
	return (path);
}