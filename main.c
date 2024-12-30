/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:41:00 by hamad             #+#    #+#             */
/*   Updated: 2024/12/30 17:02:15 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\e[32mMartho shell\e[0m# ");
		if (line)
		{
			process_input(line, envp);
			add_history(line);
			free(line);
		}
	}
	return (0);
}
