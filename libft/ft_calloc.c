/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:02:06 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/15 17:01:03 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*ptr;

	if (num * size < 1)
		return (NULL);
	ptr = (unsigned char *)malloc((num * size));
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (num * size));
	return (ptr);
}
