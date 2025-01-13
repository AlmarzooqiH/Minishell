/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:18:19 by hamad             #+#    #+#             */
/*   Updated: 2025/01/13 21:16:53 by mthodi           ###   ########.fr       */
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

char	*expand_variable(t_commands *cmds, const char *str)
{
	t_expand_vars	vars;

	vars.result = malloc(4096);
	if (!vars.result)
		return (NULL);
	vars.i = 0;
	vars.j = 0;
	expand_variable_helper(cmds, str, &vars);
	vars.result[vars.j] = '\0';
	return (vars.result);
}

void	update_envp(t_commands *cmds, int i)
{
	char	*name;
	char	*equal_pos;
	char	*expanded_value;

	equal_pos = ft_strchr(cmds->c[cmds->cc][i], '=');
	if (!equal_pos)
		return ;
	name = ft_substr(cmds->c[cmds->cc][i], 0, equal_pos - cmds->c[cmds->cc][i]);
	expanded_value = expand_variable(cmds, cmds->c[cmds->cc][i]);
	update_envp_helper(cmds, name, expanded_value);
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
