/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:18:19 by hamad             #+#    #+#             */
/*   Updated: 2025/01/26 22:57:30 by hamad            ###   ########.fr       */
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

	if (!ft_isalpha(cmds->c[cmds->cc][i][0]) && cmds->c[cmds->cc][i][0] != '_')
		return (gs_status(GET_STATUS, SET_STATUS), 0);
	j = 1;
	while (cmds->c[cmds->cc][i][j] && cmds->c[cmds->cc][i][j] != '=')
	{
		if (!ft_isalnum(cmds->c[cmds->cc][i][j])
			&& cmds->c[cmds->cc][i][j] != '_')
			return (gs_status(GET_STATUS, SET_STATUS), 0);
		j++;
	}
	return (1);
}

char	*expand_variable(t_commands *cmds, const char *str)
{
	t_expand_vars	vars;

	vars.result = malloc(BUFFER_SIZE);
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
	char	*var_name;
	char	*equal_pos;
	char	*expanded_value;
	char	*empty_value;

	equal_pos = ft_strchr(cmds->c[cmds->cc][i], '=');
	if (equal_pos)
	{
		var_name = ft_substr(cmds->c[cmds->cc][i], 0,
				equal_pos - cmds->c[cmds->cc][i]);
		expanded_value = expand_variable(cmds, cmds->c[cmds->cc][i]);
		update_envp_helper(cmds, var_name, expanded_value);
		free(var_name);
	}
	else
	{
		var_name = ft_strdup(cmds->c[cmds->cc][i]);
		empty_value = ft_strdup("");
		update_envp_helper(cmds, var_name, empty_value);
		free(var_name);
	}
}

void	builtin_export(t_commands *cmds)
{
	int		i;
	int		had_invalid;

	had_invalid = 0;
	if (!cmds->c[cmds->cc][1])
		return (gs_status(SET_STATUS, SET_STATUS), print_envp(cmds->envp));
	i = 1;
	while (cmds->c[cmds->cc][i])
	{
		if (!is_valid_identifier(cmds, i))
			handle_invalid_identifier(cmds, i, &had_invalid);
		else
			handle_valid_identifier(cmds, i);
		i++;
	}
	if (had_invalid)
		gs_status(GET_STATUS, SET_STATUS);
}
