/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:30:55 by hamad             #+#    #+#             */
/*   Updated: 2024/10/14 17:36:50 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_split(char **s)
{
	size_t	i;
	size_t	size;

	if (!s || !s[0])
		ft_printf("%s\n", NULL);
	i = 0;
	size = count_split(s);
	ft_printf("{");
	while (s[i])
	{
		if (i == size)
		{
			ft_printf("%s", s[i]);
			break ;
		}
		ft_printf("%s, ", s[i]);
		i++;
	}
	ft_printf("%s", s[i]);
	ft_printf("}\n");
}
