/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:25 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/16 13:35:44 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_next_quote(char *dest, char *src, int *dest_i, int *src_i)
{
	char	quote_type;

	if (!src)
		return ;
	quote_type = src[*src_i];
	(*src_i)++;
	while (src[*src_i] != quote_type && src[*src_i] != '\0')
	{
		if (dest)
			dest[*dest_i] = src[*src_i];
		(*dest_i)++;
		(*src_i)++;
	}
	if (src[*src_i] == quote_type)
		(*src_i)++;
}

static int	ft_count_unquoted_char(char *str)
{
	int	src_i;
	int	dest_i;

	src_i = 0;
	dest_i = 0;
	while (str[src_i] != '\0')
	{
		if (str[src_i] == '\"' || str[src_i] == '\'')
			ft_next_quote(NULL, str, &dest_i, &src_i);
		else
		{
			src_i++;
			dest_i++;
		}
	}
	return (dest_i);
}

char	*ft_get_unquoted_str(char *str)
{
	char	*unquoted;
	int		i;
	int		j;

	j = 0;
	i = 0;
	unquoted = ft_calloc((ft_count_unquoted_char(str) + 1), sizeof(char));
	if (!unquoted)
		return (NULL);
	while (str[j])
	{
		if (str[j] == '\"' || str[j] == '\'')
			ft_next_quote(unquoted, str, &i, &j);
		else
		{
			unquoted[i] = str[j];
			i++;
			j++;
		}
	}
	unquoted[i] = '\0';
	return (unquoted);
}

char	*ft_list_getenv(char *var_key, t_env *env_list, t_env *user_env_list)
{
	while (env_list)
	{
		if (ft_strlen(env_list->key) == ft_strlen(var_key)
			&& (ft_strncmp(var_key, env_list->key, ft_strlen(var_key)) == 0))
			return (env_list->value);
		env_list = env_list->next;
	}
	while (user_env_list)
	{
		if (ft_strlen(user_env_list->key) == ft_strlen(var_key)
			&& (ft_strncmp(var_key, user_env_list->key,
					ft_strlen(var_key)) == 0))
			return (user_env_list->value);
		user_env_list = user_env_list->next;
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
