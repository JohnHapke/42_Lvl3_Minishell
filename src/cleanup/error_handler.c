/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:15 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:41:25 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_handler(t_error_code error_code, int *exit_status)
{
	(void) error_code;
	perror(strerror(errno));
	*exit_status = (int)error_code;
}
