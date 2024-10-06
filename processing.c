/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2024/10/06 22:19:21 by hamad            ###   ########.fr       */
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
	else
		execute_binary(commands, NULL);
}

/*
	@brief				This function will process the passed commands that c-
						-ontain pipes.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
*/
void	process_commands_wp(char ***commands, size_t len)
{
	size_t	i;
	char	**av;

	i = 0;
	while (commands[i] && i < len)
	{
		process_commands(commands[i], count_split(commands[i]));
		i++;
		av = create_argv();
		if (!av)
			return ;
		if (commands[i])
			execute_binary(commands[i], av);
		free_split(av);
	}
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
	char	**temp_split;
	int		n_pipes;

	n_pipes = has_pipe((char *)command);
	if (n_pipes >= 1)
	{
		tokens = (char ***)malloc(sizeof(char **) * (n_pipes + 1));
		if (!tokens)
			return ;
		get_tokens((char *)command, tokens, '|');
		process_commands_wp(tokens, n_pipes);
		free_tokens(tokens, n_pipes);
		tokens = NULL;
	}
	else
	{
		temp_split = ft_split((char *)command, ' ');
		if (!temp_split || !temp_split[0])
			return ;
		process_commands(temp_split, count_split(temp_split));
		free_split(temp_split);
	}
}
