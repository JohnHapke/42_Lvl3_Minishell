/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:02:39 by iherman-          #+#    #+#             */
/*   Updated: 2025/06/24 14:30:34 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	debug_list_print(t_shell *shell, t_token *token_list, t_command *command)
{
	t_env	*current;
	int		i;

	i = 0;
	current = shell->env_list;
	printf("Environment:\n");
	while (current)
	{
		printf("	Key:	%s\n", current->key);
		printf("	Value:	%s\n", current->value);
		current = current->next;
	}
	printf("Token list:\n");
	while (token_list)
	{
		printf("%s\n", token_list->value);
		token_list = token_list->next;
	}
	printf("Commands:\n");
	while (command)
	{
		printf("1\n");
		while (command->redirs)
		{
			printf("redir type : %i\n", command->redirs->type);
			printf("redir file : %s\n", command->redirs->file);
			command->redirs = command->redirs->next;
		}
		i = 0;
		printf("2\n");
		while (command->args[i])
		{
			printf("command  args : %s\n", command->args[i]);
			i++;
		}
		printf("3\n");
		command = command->next;
	}
} /*temporary debug*/

void	ft_parsing_handler(t_shell *shell, t_token *token_list)
{
	t_command	*command;
	t_env		*env;

	env = NULL;
	command = NULL;
	if (ft_token_validator(token_list) == 1)
		ft_error_handler();
	ft_expansion_handler(shell, &token_list);
	ft_command_handler(token_list, &command);
	debug_list_print(shell, token_list, command);
}
