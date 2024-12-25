/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:49 by hamad             #+#    #+#             */
/*   Updated: 2024/12/25 14:36:02 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will free the variables from ft_execute2().
*/
void	free_variables(char **t, char **y, char **u, char **s)
{
	if (t)
		free_split(t);
	if (y)
		free_split(y);
	if (u)
		free_split(u);
	if (s)
		free_split(s);
}
