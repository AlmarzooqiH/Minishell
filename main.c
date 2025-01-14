/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:41:00 by hamad             #+#    #+#             */
/*   Updated: 2025/01/14 21:06:44 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = -1;
// int	main(int ac, char **av, char **envp)
// {
// 	char	*line;

// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		line = readline("\e[32mMartho shell\e[0m# ");
// 		if (line)
// 		{
// 			init_signals();
// 			process_input(line, envp);
// 			add_history(line);
// 			free(line);
// 		}
// 	}
// 	return (0);
// }

/**
 * @brief get or set status.
 * @param st status to set.
 * @param gors 1 to get, 0 to set.
 * @return status.
 */
int	gs_status(int st, int gors)
{
	static int	status;
	static int	flag;

	if (flag == 0)
	{
		status = 0;
		flag = 1;
	}
	if (gors == 1)
		return (status);
	else if (gors == 0)
		status = st;
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	init_signals();
	while (1)
	{
		line = readline("\e[32mMartho shell\e[0m# ");
		if (!line)
		{
			builtin_exit(NULL);
			free(line);
		}
		if (line)
		{
			process_input(line, envp);
			add_history(line);
			free(line);
		}
	}
	return (0);
}
