/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:48 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 21:09:43 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	validate_command(char ***command)
{
	size_t	i;
	size_t	j;

	if (!command || !(*command))
		return (1);
	i = 0;
	while (command[i])
	{
		while (command[i][j])
		{
			if (is_redirection(command[i][j]) >= 0 && (!command[i][j + 1]
					|| is_redirection(command[i][j + 1]) >= 0))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
