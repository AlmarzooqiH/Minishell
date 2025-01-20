/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:42:18 by root              #+#    #+#             */
/*   Updated: 2025/01/20 19:57:57 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	remove_env_var(char **envp, int index)
{
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
	free(envp[index]);
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
