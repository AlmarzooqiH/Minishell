/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:38:31 by hamad             #+#    #+#             */
/*   Updated: 2025/01/23 20:15:27 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will check if the string is numeric.
 * @param str The string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
int	is_numeric(const char *str)
{
	int	i;

	if (!str)
		return (0);
	if (is_quote(str[0]))
		i = 1;
	else
		i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (is_quote(str[i]))
			break ;
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

	if (cmds && cmds->c[cmds->cc][1])
	{
		if (!is_numeric(cmds->c[cmds->cc][1]))
		{
			ft_putstr_fd(cmds->c[cmds->cc][1], 2);
			ft_putendl_fd("exit: numeric argument required", 2);
			free_cmds(cmds);
			exit(255);
		}
		if (count_tokens(cmds->c[cmds->cc]) >= 3)
			return (gs_status(1, SET_STATUS),
				ft_putendl_fd("exit: too many arguments", 2));
		es = ft_atoll(cmds->c[cmds->cc][1]);
		es = es & 255;
	}
	else
		es = gs_status(0, GET_STATUS);
	if (cmds)
		free_cmds(cmds);
	exit((int)es);
}
