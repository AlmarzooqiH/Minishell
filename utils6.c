/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:53:27 by hamalmar          #+#    #+#             */
/*   Updated: 2025/01/22 23:53:27 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_isprefix(envp[i], "PATH="))
			return (i);
		i++;
	}
	return (-1);
}
