/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:11:39 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/28 13:47:28 by hamad            ###   ########.fr       */
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

void	update_envp_helper(t_commands *cmds, char *name, char *expv)
{
	int		i;
	char	**new_envp;

	new_envp = ft_calloc(sizeof(char *), count_tokens(cmds->envp) + 2);
	if (!new_envp)
		return (perror(FAME), exit(GET_STATUS));
	i = 0;
	while (i < count_tokens(cmds->envp))
	{
		if (ft_exp_isprefix(cmds->envp[i], name))
			new_envp[i] = update_envp2(name, expv);
		else
			new_envp[i] = ft_strdup(cmds->envp[i]);
		if (!new_envp[i])
			return (free_split(new_envp), perror(FAM), exit(GET_STATUS));
		i++;
	}
	if (!is_in(cmds->envp, name))
	{
		if (expv[0] != '\0')
			new_envp[i++] = ft_strdup(expv);
		else
			new_envp[i++] = ft_strdup(name);
	}
	return (new_envp[i] = NULL, feasage(cmds, new_envp, expv));
}

void	handle_invalid_identifier(t_commands *cmds, int i, int *had_invalid)
{
	printf("export: `%s': not a valid identifier\n", cmds->c[cmds->cc][i]);
	*had_invalid = 1;
	gs_status(GET_STATUS, SET_STATUS);
}
