/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2025/01/09 11:54:21 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
	@brief			This function will split the command that was passed by the
					user and it will split/tokenize it. Then it will pass the
					tokenized input to process_commands / process_commands_wp.
	@param	command	This holds the user input before splitting/tokenizing it.
*/
void	process_input(const char *command, char **envp)
{
	t_commands	*cmds;

	(void)cmds;
	(void)envp;
	if (!command || !command[0] || command[0] == '\0')
		return ;
	if (!validate_command((char *)command))
		return ;
	cmds = (t_commands *)malloc(sizeof(t_commands));
	init(cmds, command);
	if (!cmds)
		return ;
	cmds->envp = envp;
	execute_binary(cmds);
	free_cmds(cmds);
	free(cmds);
	cmds = NULL;
}
