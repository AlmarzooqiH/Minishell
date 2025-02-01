/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 18:11:09 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
	@brief			This function will split the command that was passed by the
					user and it will split/tokenize it. Then it will pass the
					tokenized input to process_commands / process_commands_wp.
	@param	command	This holds the user input before splitting/tokenizing it.
*/
void	process_input(const char *command)
{
	t_commands	*cmds;

	if (!command || !command[0] || command[0] == '\0')
		return ;
	if (!validate_command((char *)command))
		return ;
	cmds = (t_commands *)malloc(sizeof(t_commands));
	if (!cmds)
		return ;
	init(cmds, command);
	execute_binary(cmds);
	free_cmds(cmds);
	free(cmds);
	cmds = NULL;
}
