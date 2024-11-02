/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:16 by hamad             #+#    #+#             */
/*   Updated: 2024/10/29 17:06:50 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will count the number of redirections that are prese-
 * 			-nt within the command.
 * @param	command This holds the command that was passed.
 * @param	len		This holds the length of the command.
 * @return	Will return the number of redirections within the command.
 */
size_t	count_redirections(char **command, size_t len)
{
	size_t	n;
	size_t	i;

	if (!command)
		return (0);
	i = 0;
	n = 0;
	while (i < len)
	{
		if (ft_strcmp(command[i], REDICERTION_TO_FILE))
			n++;
		else if (ft_strcmp(command[i], REDIRECTION_TO_INPUT))
			n++;
		else if (ft_strcmp(command[i], APPEND_REDIRECTION))
			n++;
		else if (ft_strcmp(command[i], HEREDOC_REDIRECTION))
			n++;
		i++;
	}
	return (n);
}
