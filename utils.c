/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:26:39 by hamad             #+#    #+#             */
/*   Updated: 2024/09/30 23:42:26 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
	@brief	This function will check if the passed commands contain a pipe('|')
	@param	commands	This will hold all of the commands passed by the shell.
	@param	len			This holds the length of the commands.
*/
int	has_pipe(char **commands, size_t len)
{
	size_t	i;
	size_t	j;

	if (!commands || !(*commands))
		return (0);
	while (i < len)
	{
		j = ft_skipspace(commands[i]);
		while (commands[i][j])
		{
			if (commands[i][j] == '|')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		has_flag(char *flag, char *flag_in)
{
	return (ft_strcmp(flag_in, flag));
}
