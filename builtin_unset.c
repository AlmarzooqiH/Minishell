/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:42:18 by root              #+#    #+#             */
/*   Updated: 2025/02/01 10:43:33 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	remove_env_var(t_commands *cmds, int index)
{
	int		i;
	char	**new_envp;

	new_envp = ft_calloc(sizeof(char *), count_tokens(cmds->envp) + 1);
	if (!new_envp)
		return (perror(FAME), exit(GET_STATUS));
	i = 0;
	while (i < index)
	{
		new_envp[i] = ft_strdup(cmds->envp[i]);
		i++;
	}
	i++;
	while (cmds->envp[i])
	{
		new_envp[i - 1] = ft_strdup(cmds->envp[i]);
		i++;
	}
	gs_envp(new_envp, SET_ENVP);
	free_split(cmds->envp);
	cmds->envp = new_envp;
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

void	unset_env_var(t_commands *cmds, const char *var)
{
	int	j;

	j = 0;
	while (cmds->envp[j])
	{
		if (ft_strncmp(var, cmds->envp[j], ft_strlen(var)) == 0
			&& (cmds->envp[j][ft_strlen(var)]
			== '=' || cmds->envp[j][ft_strlen(var)] == '\0'))
		{
			remove_env_var(cmds, j);
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
			unset_env_var(cmds, cmds->c[cmds->cc][i]);
		i++;
	}
	gs_status(SET_STATUS, SET_STATUS);
}
