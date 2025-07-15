/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:04:04 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/15 16:57:02 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*sub;

	i = 0;
	if (start >= ft_strlen(s))
		sub = ((char *)ft_calloc(sizeof(char), 1));
	else if ((len + start) > ft_strlen(s))
		sub = (char *)ft_calloc(((ft_strlen(s) - start) + 1), sizeof(char));
	else
		sub = (char *)ft_calloc((len + 1), sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
