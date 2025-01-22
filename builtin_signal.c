/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:41:08 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/22 21:30:09 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	child_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		gs_status(130, SET_STATUS);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	signal_handler(int signal_num)
{
	if (signal_num == SIGINT)
	{
		gs_status(130, SET_STATUS);
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = child_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_DFL);
}
