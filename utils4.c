/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:05:57 by hamad             #+#    #+#             */
/*   Updated: 2024/12/19 15:05:07 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	Will check if the command has redirection or not.
 * @param	cmd	Will hold the command struct.
 * @return	1 if the command has redirection, 0 otherwise.
 */
int	has_redirection(t_commands *cmds)
{
	int	i;

	if (!cmds->rd)
		return (0);
	i = 0;
	while (i < count_tokens(cmds->cmds[cmds->cc]))
	{
		if (cmds->rd[cmds->cc][i] >= 0)
			return (1);
		i++;
	}
	return (0);
}
