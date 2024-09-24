/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:03:10 by hamad             #+#    #+#             */
/*   Updated: 2024/09/24 14:14:31 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(const char *command)
{
	char	**split;
	size_t	split_size;
	size_t	i;

	split = ft_split(command, ' ');
	split_size = count_split(split);
	if (!split || !*split || !split_size || split_size == 1)
	{
		free_split(split);
		return ;
	}
	i = 0;
	while (i < split_size)
	{
		if (ft_strcmp(split[i], ECHO_COMMAND))
		{
			printf("%s\n", split[i + 1]);
			break ;
		}
		i++;
	}
}
