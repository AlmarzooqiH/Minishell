/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:30:55 by hamad             #+#    #+#             */
/*   Updated: 2024/11/08 23:03:45 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_split(char **s)
{
	size_t	i;
	size_t	size;

	if (!s || !s[0 || !s[0][0]])
		return (ft_printf("%s\n", NULL), (void)NULL);
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
