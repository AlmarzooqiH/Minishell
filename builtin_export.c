/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:18:19 by hamad             #+#    #+#             */
/*   Updated: 2025/01/05 14:02:22 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	is_valid_identifier(t_commands *cmds, int i)
{
	int	j;

	if (!isalpha(cmds->c[cmds->cc][i][0]) && cmds->c[cmds->cc][i][0] != '_')
		return (0);
	j = 1;
	while (cmds->c[cmds->cc][i][j] && cmds->c[cmds->cc][i][j] != '=')
	{
		if (!isalnum(cmds->c[cmds->cc][i][j]) && cmds->c[cmds->cc][i][j] != '_')
			return (0);
		j++;
	}
	return (1);
}

void	update_envp(t_commands *cmds, int i)
{
	int		j;
	char	*name;
	char	*equal_pos;

	equal_pos = ft_strchr(cmds->c[cmds->cc][i], '=');
	if (!equal_pos)
		return ;
	name = ft_substr(cmds->c[cmds->cc][i], 0, equal_pos - cmds->c[cmds->cc][i]);
	j = 0;
	while (cmds->envp[j])
	{
		if (ft_strncmp(name, cmds->envp[j], ft_strlen(name)) == 0
			&& cmds->envp[j][ft_strlen(name)] == '=')
		{
			free(cmds->envp[j]);
			cmds->envp[j] = ft_strdup(cmds->c[cmds->cc][i]);
			free(name);
			return ;
		}
		j++;
	}
	cmds->envp[j] = ft_strdup(cmds->c[cmds->cc][i]);
	cmds->envp[j + 1] = NULL;
	free(name);
}

void	builtin_export(t_commands *cmds)
{
	int	i;

	if (!cmds->c[cmds->cc][1])
	{
		print_envp(cmds->envp);
		return ;
	}
	i = 1;
	while (cmds->c[cmds->cc][i])
	{
		if (!is_valid_identifier(cmds, i))
		{
			printf("export: `%s': not a valid identifier\n",
				cmds->c[cmds->cc][i]);
			g_exit_status = 1;
		}
		else
			update_envp(cmds, i);
		i++;
	}
	g_exit_status = 0;
}
