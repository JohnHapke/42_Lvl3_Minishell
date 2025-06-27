/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/27 14:31:31 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_handler(t_error_code error_code, int *exit_status)
{
	(void) error_code;
	perror(strerror(errno));
	*exit_status = (int)error_code;
}
