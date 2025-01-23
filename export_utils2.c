/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:35:30 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/23 18:35:35 by mthodi           ###   ########.fr       */
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
	}
	else
		update_envp(cmds, i);
}
