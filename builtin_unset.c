/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:42:18 by root              #+#    #+#             */
/*   Updated: 2025/01/15 19:49:25 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	remove_env_var(char **envp, int index)
{
	free(envp[index]);
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
}

void	builtin_unset(t_commands *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds->c[cmds->cc][i])
	{
		j = 0;
		while (cmds->envp[j])
		{
			if (ft_strncmp(cmds->c[cmds->cc][i], cmds->envp[j],
				ft_strlen(cmds->c[cmds->cc][i])) == 0)
			{
				remove_env_var(cmds->envp, j);
				break ;
			}
			j++;
		}
		i++;
	}
	gs_status(SET_STATUS, SET_STATUS);
}
