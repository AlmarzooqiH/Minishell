/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:35:30 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/26 21:53:10 by hamad            ###   ########.fr       */
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
		if (!ft_isprefix(envp[i], name))
			count++;
		i++;
	}
	return (count);
}

char	*update_envp2(char *name, char *exp)
{
	char	*new_s;

	if (!name || !exp)
		return (NULL);
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
		if (ft_isprefix(envp[i], name))
			return (1);
		i++;
	}
	return (0);
}
