/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:11:28 by hamad             #+#    #+#             */
/*   Updated: 2024/09/24 13:11:58 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_split(char **argv)
{
	size_t	count;

	if (!argv)
		return (0);
	count = 0;
	while (argv[count])
		count++;
	return (count);
}
