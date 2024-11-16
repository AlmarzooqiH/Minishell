/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:49:25 by truedevelop       #+#    #+#             */
/*   Updated: 2024/11/14 01:14:30 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(size_t len, ...)
{
	size_t	i;
	size_t	j;
	va_list	args;
	char	**s;

	if (len == 0)
		return ;
	va_start(args, len);
	i = 0;
	while (i < len)
	{
		s = va_arg(args, char **);
		if (s)
		{
			j = 0;
			while (s[j])
			{
				free(s[j]);
				j++;
			}
			free(s);
		}
		i++;
	}
	va_end(args);
}
