/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:58:22 by mthodi            #+#    #+#             */
/*   Updated: 2024/10/08 16:21:37 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_status;

	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
			exit_status = 255;
		}
		else if (args[2])
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			return (1);  // Error but don't exit the shell
		}
		else
			exit_status = atoi(args[1]) % 256;
	}
	else
		exit_status = 0;
	exit(exit_status);
}
