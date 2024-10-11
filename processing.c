/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2024/10/11 16:21:05 by hamad            ###   ########.fr       */
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
void	process_commands(char ***commands, size_t len)
{
	if (ft_strcmp(commands[0][0], ECHO_COMMAND))
		process_echo(commands[0], count_split(commands[0]));
	else
		execute_binary(commands, len);
}

/*
	@brief				This function will process the passed commands that c-
						-ontain pipes.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
	@var	temp_av		This will hold the stdout of the prevoius command temp-
						-orarly.
	@var	av			This will hold the second command + flags and the temp-
						-_av which will be passed to execute_binary.
*/
void	process_commands_wp(char ***commands, size_t len)
{
	execute_binary(commands, len);
}

/*
	@brief			This function will split the command that was passed by the
					user and it will split/tokenize it. Then it will pass the
					tokenized input to process_commands / process_commands_wp.
	@param	command	This holds the user input before splitting/tokenizing it.
*/
void	process_input(const char *command)
{
	char	***tokens;
	int		n_pipes;

	if (command[0] == '\0')
		return ;
	n_pipes = has_pipe((char *)command);
	tokens = (char ***)malloc(sizeof(char **) * (n_pipes + 1));
	if (!tokens)
		return ;
	get_tokens((char *)command, tokens, '|');
	if (n_pipes > 1)
	{
		process_commands_wp(tokens, n_pipes);
		tokens = NULL;
	}
	else
		process_commands(tokens, n_pipes);
	free_tokens(tokens, n_pipes);
}
