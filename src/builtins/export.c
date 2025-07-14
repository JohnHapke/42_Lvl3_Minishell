/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:24 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/14 09:10:09 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* functional use case:
1.	minishell$ export

2.	minishell$ VAR=hello
	minishell$ export VAR

not implemented:
1.	minishell$ export HELLO=hello
	minishell$ env | grep HELLO

2. error handling
*/



/* Only used when variable key is invalid: e.g. "//varkey" is invalid due to characters */
/*static int	ft_export_error_message(char *identifier)
{
	ft_putstr_fd("Export: ", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd(": is not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}*/
/*static void	ft_envus_lstclear(t_env **lst)
{
	t_env	*temp;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free((*lst));
		*lst = temp;
	}
	*lst = NULL;
}*/

static int	ft_find_equal_sign(char	*var)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_export(t_shell *shell, char **argv)
{
	t_env	*current_user_env;
	char	*str;
	int		equal_sign;

	if (!argv[1])
		return (ft_env(shell, argv));
	current_user_env = shell->user_env_list;
	equal_sign = ft_find_equal_sign(argv[1]);
	str = NULL;
	if (argv[1])
	{
		while (current_user_env != NULL)
		{
			str = ft_strdup(current_user_env->key);
			if (equal_sign > -1)
			{
				str = ft_strjoin(str, "=");
				str = ft_strjoin(str, current_user_env->value);
			}
			if (ft_strncmp(str, argv[1], ft_strlen(str)) == 0 && ft_strlen(str))
			{
				ft_env_add_back(&shell->env_list, ft_env_new_node(current_user_env->key, current_user_env->value));
				//ft_envus_lstclear(&current_user_env);
				ft_env(shell, argv);
				free (str);
				return (EXIT_SUCCESS);
			}
			free (str);
			current_user_env= current_user_env->next;
		}
	}
	return (EXIT_FAILURE);
}
