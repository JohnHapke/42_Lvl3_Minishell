/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnhapke <johnhapke@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:28:13 by iherman-          #+#    #+#             */
/*   Updated: 2025/07/16 08:25:11 by johnhapke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_lstclear(t_env **lst)
{
	t_env	*temp;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->key);
		free((*lst)->value);
		free((*lst));
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_cleanup_shell(t_shell *shell)
{
	ft_free_all(shell->env_array);
	ft_env_lstclear(&shell->env_list);
	ft_env_lstclear(&shell->user_env_list);
}
