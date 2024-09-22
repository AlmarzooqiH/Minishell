/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:04:45 by hamalmar          #+#    #+#             */
/*   Updated: 2023/12/05 20:04:48 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	current_s;
	unsigned char	compare_c;

	compare_c = (unsigned char)(c);
	while (*s)
	{
		current_s = (unsigned char)(*s);
		if (current_s == compare_c)
			return ((char *)s);
		s++;
	}
	current_s = (unsigned char)(*s);
	if (current_s == compare_c)
		return ((char *)s);
	return (0);
}
