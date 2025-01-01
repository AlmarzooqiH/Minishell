/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:41:08 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/01 20:48:44 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Configures and handles signals for the minishell.
 * @param signal_num The signal number to be handled.
 * @return Void.
 */
void	signal_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal_num == SIGQUIT)
		printf("Quit: 3\n");
}

void	init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, SIG_IGN);
}
