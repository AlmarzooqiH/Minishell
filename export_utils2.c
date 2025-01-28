/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:35:30 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/28 08:05:23 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_valid_identifier(t_commands *cmds, int i)
{
	char	*equal_pos;
	char	*var_name;
	char	*empty_value;

	equal_pos = ft_strchr(cmds->c[cmds->cc][i], '=');
	if (!equal_pos)
	{
		var_name = ft_strdup(cmds->c[cmds->cc][i]);
		empty_value = ft_strdup("");
		update_envp_helper(cmds, var_name, empty_value);
		free(var_name);
		free(empty_value);
	}
	else
		update_envp(cmds, i);
}

//Count envp elements that are not equal to name.
int	cet(char **envp, char *name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (!ft_exp_isprefix(envp[i], name))
			count++;
		i++;
	}
	return (count);
}

char	*update_envp2(char *name, char *exp)
{
	char	*new_s;
	char	*equals;

	if (!name)
		return (NULL);
	equals = ft_strchr(exp, '=');
	if (!equals)
		return (ft_strdup(name));
	new_s = ft_strjoin(name, ft_strchr(exp, '='));
	if (!new_s)
		return (perror("Failed to join env"), NULL);
	return (new_s);
}

int	is_in(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_exp_isprefix(envp[i], name))
			return (1);
		i++;
	}
	return (0);
}

//free expv and set and get envp
void	feasage(t_commands *cmds, char **new_envp, char *expv)
{
	free_split(cmds->envp);
	gs_envp(new_envp, SET_ENVP);
	if (expv && expv[0] != '\0')
		free(expv);
	cmds->envp = gs_envp(NULL, GET_ENVP);
}
