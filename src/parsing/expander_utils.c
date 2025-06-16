/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:25 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/16 15:40:45 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_variable_check(char *value)
{
	int	i;

	i = -1;
	if (ft_strchr(value, '=') == NULL || ft_isdigit(value[0]))
		return (false);
	while (value[i++] != '=')
	{
		if (ft_isalnum(value[i]) && value[i] != '_')
			return (false);
	}
	return (true);
}

int	ft_count_char(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != "\"")
			j++;
		i++;
	}
	return (j);
}

char	*ft_get_unquoted_str(char *str)
{
	char	*unquoted;
	int		i;

	unquoted = malloc((ft_count_char(str) + 1) * sizeof(char));
	if (!unquoted)
		return (NULL);
	while (*str != "=")
		str++;
	str++;
	i = -1;
	while ((*str))
	{
		if (*str != "\"")
			unquoted[++i] = *str;
		str++;
	}
	unquoted[i] = '\0';
	return (unquoted);
}
