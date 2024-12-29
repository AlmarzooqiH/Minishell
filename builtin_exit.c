/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:38:31 by hamad             #+#    #+#             */
/*   Updated: 2024/12/29 16:33:49 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief This function will replicate the exit function.
 * @param cmds The commands structure.
 * @return void
 */
void	builtin_exit(t_commands *cmds)
{
	int	es;

	printf("exit\n");
	if (cmds->c[cmds->cc][1] && !is_numeric(cmds->c[cmds->cc][1]))
	{
		printf("exit: %s: numeric argument required\n", cmds->c[cmds->cc][1]);
		free_cmds(cmds);
		exit(255);
	}
	if (count_tokens(cmds->c[cmds->cc]) > 2)
	{
		printf("exit: too many arguments\n");
		cmds->es = 1;
		return ;
	}
	if (cmds->c[cmds->cc][1])
		es = ft_atoi(cmds->c[cmds->cc][1]);
	free_cmds(cmds);
	exit(es);
}
