/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:41:00 by hamad             #+#    #+#             */
/*   Updated: 2024/12/23 17:33:01 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("\e[32mMartho shell\e[0m# ");
		if (line)
		{
			process_input(line);
			add_history(line);
			free(line);
		}
	}
	return (0);
}
