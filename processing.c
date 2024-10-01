/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2024/10/01 16:25:43 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
	@brief				This function will process the passed commands. This
						function do not process with pipes. If you want to pro-
						-cess with pipes refer to process_commands_wp() which
						has the capability to process the commands with pipes.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
*/
void	process_commands(char **commands, size_t len)
{
	if (ft_strcmp(commands[0], ECHO_COMMAND))
		process_echo(commands, len);
}

/*
	@brief				This function will process the passed commands that c-
						-ontain pipes.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
*/
void	process_commands_wp(char **commands, size_t len)
{
	(void)commands;
	(void)len;
}

/*
	@brief			This function will split the command that was passed by the
					user and it will split/tokenize it. Then it will pass the
					tokenized input to process_commands / process_commands_wp.
	@param	command	This holds the user input before splitting/tokenizing it.
*/
void	process_input(const char *command)
{
	char	**split;
	size_t	len;

	split = ft_split(command, ' ');
	len = count_split(split);
	if (!split || !*split || !len)
	{
		free_split(split);
		return ;
	}
	if (has_pipe(split, len))
		process_commands_wp(split, len);
	else
		process_commands(split, len);
	free_split(split);
}
