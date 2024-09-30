/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2024/09/30 23:50:27 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	process_commands(char **commands, size_t len)
{
	if (ft_strcmp(commands[0], ECHO_COMMAND))
		process_echo(commands, len);
}
void	process_commands_wp(char **commands, size_t len)
{
	(void)commands;
	(void)len;
}
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
