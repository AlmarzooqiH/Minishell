/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:10:04 by hamad             #+#    #+#             */
/*   Updated: 2025/01/23 17:56:52 by mthodi           ###   ########.fr       */
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
		if (ft_strchr(cmds->envp[i], '=') != 0)
			printf("%s\n", cmds->envp[i]);
		i++;
	}
	gs_status(GET_STATUS, SET_STATUS);
}
