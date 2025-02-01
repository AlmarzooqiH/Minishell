/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:41:00 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 16:55:38 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (gors == GET_STATUS)
		return (status);
	else if (gors == SET_STATUS)
		status = st;
	return (status);
}

char	**gs_envp(char **envp, int gore)
{
	static char	**env;

	if (gore == INIT_ENVP && envp != NULL)
	{
		env = ft_dup_split(envp);
		if (!env || !env[0])
			return (perror("Failed to dup env"), NULL);
	}
	if (gore == GET_ENVP)
		return (env);
	else if (gore == SET_ENVP)
		env = envp;
	else if (gore == EXIT_ENVP)
	{
		if (env)
			free_split(env);
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	init_signals();
	gs_envp(envp, INIT_ENVP);
	while (1)
	{
		line = readline("Martho shell# ");
		if (!line)
		{
			builtin_exit(NULL);
			free(line);
		}
		if (line)
		{
			process_input(line);
			add_history(line);
			free(line);
		}
	}
	return (0);
}
