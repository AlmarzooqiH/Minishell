/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/09/30 21:53:48 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	process_echo(char **commands, size_t len)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < len)
	{
		j = 0;
		while(commands[i][j])
		{
			if(commands[i][j] == '\'' || commands[i][j] == '\"')
				j++;
			write(STDOUT_FILENO, &commands[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
