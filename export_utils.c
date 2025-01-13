/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:11:39 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/13 21:17:46 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	expand_variable_helper(t_commands *cmds, const char *str,
	t_expand_vars *vars)
{
	char	*var_name;
	char	*value;

	while (str[vars->i])
	{
		if (str[vars->i] == '$')
		{
			vars->i++;
			var_name = get_var_name(str, &vars->i);
			value = get_env_value(cmds, var_name);
			if (value)
			{
				ft_strcpy(vars->result + vars->j, value);
				vars->j += ft_strlen(value);
			}
			free(var_name);
		}
		else
			vars->result[vars->j++] = str[vars->i++];
	}
}

char	*get_var_name(const char *str, int *i)
{
	int		k;
	char	var_name[256];

	k = 0;
	ft_memset(var_name, 0, sizeof(var_name));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[k++] = str[(*i)++];
	return (ft_strdup(var_name));
}

char	*get_env_value(t_commands *cmds, const char *var_name)
{
	int		env_i;
	char	*value;

	env_i = 0;
	while (cmds->envp[env_i])
	{
		if (ft_strncmp(cmds->envp[env_i], var_name, ft_strlen(var_name)) == 0
			&& cmds->envp[env_i][ft_strlen(var_name)] == '=')
		{
			value = cmds->envp[env_i] + ft_strlen(var_name) + 1;
			return (value);
		}
		env_i++;
	}
	return (NULL);
}

void	update_envp_helper(t_commands *cmds, char *name, char *expanded_value)
{
	int		j;

	j = 0;
	while (cmds->envp[j])
	{
		if (ft_strncmp(name, cmds->envp[j], ft_strlen(name)) == 0
			&& cmds->envp[j][ft_strlen(name)] == '=')
		{
			free(cmds->envp[j]);
			cmds->envp[j] = expanded_value;
			return ;
		}
		j++;
	}
	cmds->envp[j] = expanded_value;
	cmds->envp[j + 1] = NULL;
}
