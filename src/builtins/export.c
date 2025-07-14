/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:24 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/14 19:00:58 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	functional use case:
1.	minishell$ export

2.	minishell$ VAR=hello
	minishell$ export VAR

3.	minishell$ export HELLO=hello
	minishell$ env | grep HELLO
	.. now functional

4. error handling
	Still needs to be checked, looks good so far.
*/

bool	ft_isinvalid_key(char *s, char delim)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (true);
	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (s[i] != delim)
		return (true);
	return (false);
}

t_env	*ft_export_equal(t_shell *shell, char *arg, char *equal_sign)
{
	char	*new_key;
	char	*new_value;
	t_env	*found_node;

	new_key = ft_substr(arg, 0, equal_sign - arg);
	if (!new_key)
		return (NULL);
	new_value = ft_substr(equal_sign, 1, ft_strlen(equal_sign + 1));
	if (!new_value)
	{
		free(new_key);
		return (NULL);
	}
	found_node = ft_find_env_node(new_key, shell->env_list, NULL);
	if (found_node)
	{
		free(found_node->value);
		found_node->value = new_value;
		free(new_key);
	}
	else
		ft_env_add_back(&shell->env_list, ft_env_new_node(new_key, new_value));
	found_node = ft_find_env_node(arg, NULL, shell->user_env_list);
	return (found_node);
}

t_env	*ft_export_noequal(t_shell *shell, char *arg)
{
	t_env	*user_node;
	t_env	*env_node;

	user_node = ft_find_env_node(arg, NULL, shell->user_env_list);
	if (!user_node)
		return (NULL);
	env_node = ft_find_env_node(arg, shell->env_list, NULL);
	if (env_node)
	{
		free(env_node->value);
		env_node->value = ft_strdup(user_node->value);
		if (!env_node->value)
		{
			ft_other_error(E_MEM, NULL);
			return (NULL);
		}
	}
	else
	{
		ft_env_add_back(&shell->env_list, ft_env_new_node(
			ft_strdup(user_node->key), ft_strdup(user_node->value)));
	}
	return (user_node);
}

int	ft_export_single(t_shell *shell, char *arg)
{
	char	*equal_sign;
	t_env	*found_node;

	equal_sign = ft_strchr(arg, '=');
	if ((equal_sign && ft_isinvalid_key(arg, '='))
		|| (!equal_sign && ft_isinvalid_key(arg, '\0')))
		return (ft_builtin_error(1, "export", arg, "not a valid identifier"));	
	if (equal_sign)
		found_node = ft_export_equal(shell, arg, equal_sign);
	else
		found_node = ft_export_noequal(shell, arg);
	if (found_node)
		ft_extract_node(&shell->user_env_list, found_node);
	return (EXIT_SUCCESS);
}

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	int		exit_code;
	char	**new_env;

	if (!argv[1])
		return (ft_env(shell, argv));
	i = 1;
	exit_code = EXIT_SUCCESS;
	while (argv[i])
	{
		exit_code += ft_export_single(shell, argv[i]);
		i++;
	}
	if (i > 1)
	{
		ft_free_all(shell->env_array);
		new_env = ft_list_to_strv(shell->env_list);
		if (!new_env)
			exit_code = ft_other_error(E_MEM, NULL);
		shell->env_array = new_env;
	}
	if (exit_code)
		exit_code = 1;
	return (exit_code);
}
