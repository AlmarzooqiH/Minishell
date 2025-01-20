/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:38:31 by hamad             #+#    #+#             */
/*   Updated: 2025/01/19 16:16:20 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will check if the string is numeric.
 * @param str The string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
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
// void	builtin_exit(t_commands *cmds)
// {
// 	int	es;

// 	printf("Exiting shell... \n");
// 	if (cmds->c[cmds->cc][1] && !is_numeric(cmds->c[cmds->cc][1]))
// 	{
// 		printf("exit: %s: numeric argument required\n", cmds->c[cmds->cc][1]);
// 		free_cmds(cmds);
// 		exit(255);
// 	}
// 	if (count_tokens(cmds->c[cmds->cc]) > 2)
// 	{
// 		printf("exit: too many arguments\n");
// 		cmds->es = 1;
// 		return ;
// 	}
// 	if (cmds->c[cmds->cc][1])
// 		es = ft_atoi(cmds->c[cmds->cc][1]);
// 	free_cmds(cmds);
// 	exit(es);
// }
void	builtin_exit(t_commands *cmds)
{
	long long	es;

		if (count_tokens(cmds->c[cmds->cc]) >= 3)
		{
			printf("exit: too many arguments\n");
			gs_status(GET_STATUS, SET_STATUS);
			return ;
		}
	es = 0;
	if (cmds && cmds->c[cmds->cc][1])
	{
		if (!is_numeric(cmds->c[cmds->cc][1]))
		{
			ft_putstr_fd(cmds->c[cmds->cc][1], 2);
			ft_putendl_fd("exit: numeric argument required", 2);
			free_cmds(cmds);
			exit(255);
		}
		es = ft_atoi(cmds->c[cmds->cc][1]);
	}
	else
		es = gs_status(0, GET_STATUS);
	if (cmds)
		free_cmds(cmds);
	exit((int)es);
}
