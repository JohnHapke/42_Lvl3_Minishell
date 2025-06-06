/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 13:23:12 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/06 13:24:59 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_all(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i] != NULL)
	{
		free(ret[i]);
		i++;
	}
	free (ret);
	return (0);
}

static size_t	wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		b;

	i = 0;
	count = 0;
	b = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && b == 0)
		{
			count++;
			b = 1;
		}
		else if (s[i] == c)
			b = 0;
		i++;
	}
	return (count);
}

static char	*cust_strcpy(char const *s, char c, size_t start)
{
	size_t		i;
	size_t		len;
	char		*ret;

	i = 0;
	len = 0;
	while (s[start + len] != c && s[start + len] != '\0')
		len++;
	ret = (char *) malloc((len + 1) * sizeof(char));
	if (ret == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[len] = '\0';
	return (ret);
}

static void	wcpy(char const *s, char c, char **ret, int *error)
{
	size_t	i;
	size_t	j;
	int		b;

	i = 0;
	j = 0;
	b = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && b == 0)
		{
			ret[j] = cust_strcpy(s, c, i);
			if (ret[j] == NULL)
			{
				*error = 1;
				return ;
			}
			b = 1;
			j++;
		}
		else if (s[i] == c)
			b = 0;
		i++;
	}
	ret[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		error;

	error = 0;
	if (s == NULL)
		return (NULL);
	ret = (char **)malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	wcpy(s, c, ret, &error);
	if (error == 1)
	{
		ft_free_all(ret);
		return (NULL);
	}
	return (ret);
}
