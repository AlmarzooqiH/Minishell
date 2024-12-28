/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:49 by hamad             #+#    #+#             */
/*   Updated: 2024/12/28 18:00:50 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will free the variables from ft_execute2().
*/
void	free_variables(char **t, char **y, char **u, char **s)
{
	if (t)
		free_split(t);
	if (y)
		free_split(y);
	if (u)
		free_split(u);
	if (s)
		free_split(s);
}

void	is_builtin(t_commands *cmds)
{
	if (ft_strcmp(cmds->cmds[cmds->cc][0], CD_COMMAND))
		builtin_cd(cmds);
}
