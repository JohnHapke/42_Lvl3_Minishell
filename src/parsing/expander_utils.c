/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:25 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/19 15:55:13 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_variable_check(char *value)
{
	int	i;

	i = 0;
	if (ft_strchr(value, '=') == NULL || ft_isdigit(value[0]))
		return (false);
	while (value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_count_char(char *str) //does not currently distinguish between quote types
{
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote_type = str[i];
			i++;
			while (str[i] != quote_type && str[i] != '\0')
			{
				i++;
				j++;
			}
			j--;
		}
		j++;
		i++;
	}
	return (j);
}

char	*ft_get_unquoted_str(char *str)
{
	char	*unquoted;
	int		i;
	char	quote_type;

	unquoted = malloc((1) * sizeof(char));
	if (!unquoted)
		return (NULL);
	i = -1;
	while ((*str))
	{
		if (*str == '\"' || *str == '\'')
		{
			quote_type = *str;
			str++;
			while (*str != quote_type && *str != '\0')
				unquoted[++i] = *(str++);
			str++;
		}
		unquoted[++i] = *str;
		str++;
	}
	unquoted[i + 1] = '\0';
	printf("macarrones.: %s\n", unquoted);
	return (unquoted);
}

char	*ft_compare_var_keys(char *var_key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(var_key, env_list->key, ft_strlen(var_key + 1)) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
