/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:42:18 by root              #+#    #+#             */
/*   Updated: 2025/01/23 18:33:17 by mthodi           ###   ########.fr       */
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

int	is_valid_unset_identifier(const char *str)
{
	if (!str || !ft_isalpha(*str))
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	print_unset_error(const char *identifier)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd((char *)identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	unset_env_var(char **envp, const char *var)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(var, envp[j], ft_strlen(var)) == 0)
		{
			remove_env_var(envp, j);
			break ;
		}
		j++;
	}
}

void	builtin_unset(t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->c[cmds->cc][i])
	{
		if (!is_valid_unset_identifier(cmds->c[cmds->cc][i]))
			print_unset_error(cmds->c[cmds->cc][i]);
		else
			unset_env_var(cmds->envp, cmds->c[cmds->cc][i]);
		i++;
	}
	gs_status(SET_STATUS, SET_STATUS);
}
