/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:39:02 by hamalmar          #+#    #+#             */
/*   Updated: 2024/10/02 13:26:41 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_before_n(const char *buf)
{
	size_t	i;

	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	if (buf[i] == '\n')
		i++;
	return (ft_substr(buf, 0, i));
}
