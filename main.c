/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:41:00 by hamad             #+#    #+#             */
/*   Updated: 2025/01/02 16:33:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int g_exit_status = -1;
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

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	init_signals();
	while (1)
	{
		line = readline("\e[32mMartho shell\e[0m# ");
		if(!line)
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
