/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 12:54:40 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_handler(t_error_code error_code, int *exit_status)
{
	perror(strerror(errno));
	*exit_status = (int)error_code;
}
