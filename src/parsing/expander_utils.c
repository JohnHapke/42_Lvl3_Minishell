/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:25 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/24 14:30:10 by iherman-         ###   ########.fr       */
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

static int	ft_count_unquoted_char(char *str)
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
			while (str[i] != quote_type && str[i++] != '\0')
				j++;
			if (str[i])
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	*ft_get_unquoted_str(char *str)
{
	char	*unquoted;
	int		i;
	char	quote_type;

	unquoted = malloc((ft_count_unquoted_char(str) + 1) * sizeof(char));
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
		else
			unquoted[++i] = *(str++);
	}
	unquoted[i + 1] = '\0';
	return (unquoted);
}

char	*ft_compare_var_keys(char *var_key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strlen(env_list->key) == ft_strlen(var_key)
			&& (ft_strncmp(var_key, env_list->key, ft_strlen(var_key)) == 0))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ft_insert_str(char *str, char *insert, int varkey_len, int *i)
{
	char	*ret;

	if (insert == NULL)
		return (ft_strdup(str));
	ret = ft_calloc((ft_strlen(str) + ft_strlen(insert)) - varkey_len,
			sizeof(char));
	ft_memcpy(ret, str, *i);
	ft_memcpy(&ret[*i], insert, ft_strlen(insert));
	ft_memcpy(&ret[ft_strlen(insert) + *i], &str[*i + varkey_len + 2],
		ft_strlen(&str[*i + varkey_len]));
	*i += ft_strlen(str) - ft_strlen(ret);
	return (ret);
}
