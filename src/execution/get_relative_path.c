/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relative_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:17:13 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/09 15:23:36 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_other_error_wrapper(t_exec_error error, char *arg)
{
	ft_other_error(error, arg);
	return (NULL);
}

size_t	ft_strvlen(char **strv)
{
	size_t	i;

	i = 0;
	while (strv[i])
		i++;
	return (i);
}

static char	*ft_resolve_relative(char **paths)
{
	char	*resolved_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (chdir(paths[i]))
			return (ft_other_error_wrapper(E_OTHER, paths[i]));
		i++;
	}
	temp = getcwd(NULL, 0);
	if (!temp)
		return (ft_other_error_wrapper(E_MEM, ""));
	resolved_path = ft_strjoin(temp, "/");
	free(temp);
	if (!resolved_path)
		return (ft_other_error_wrapper(E_MEM, ""));
	return (resolved_path);
}

char	*ft_get_relative_cmd_path(char *cmd)
{
	char	**paths;
	char	*cmd_name;
	char	*full_path;
	char	*sub_path;

	paths = ft_split(cmd, '/');
	if (!paths)
		return (ft_other_error_wrapper(E_MEM, ""));
	cmd_name = paths[ft_strvlen(paths) - 1];
	paths[ft_strvlen(paths) - 1] = NULL;
	sub_path = ft_resolve_relative(paths);
	if (!sub_path)
		return (ft_other_error_wrapper(E_MEM, ""));
	full_path = ft_strjoin(sub_path, cmd_name);
	if (!full_path)
		return (ft_other_error_wrapper(E_MEM, ""));
	free(cmd_name);
	free(sub_path);
	ft_free(paths);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}
