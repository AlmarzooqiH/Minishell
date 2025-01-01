/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:10:04 by hamad             #+#    #+#             */
/*   Updated: 2025/01/01 20:47:59 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Executes the env builtin command, printing the environment variables.
 * @param cmds The structure containing the parsed commands.
 * @param pos The starting position of the arguments for env.
 * @return Void.
 */
void	builtin_env(t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->envp[i])
	{
		printf("%s\n", cmds->envp[i]);
		i++;
	}
}
