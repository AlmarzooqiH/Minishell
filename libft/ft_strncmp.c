/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:42:18 by hamalmar          #+#    #+#             */
/*   Updated: 2023/12/01 19:08:34 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	current_char1;
	unsigned char	current_char2;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		current_char1 = (unsigned char)s1[i];
		current_char2 = (unsigned char)s2[i];
		if (current_char1 > current_char2)
			return (1);
		else if (current_char1 < current_char2)
			return (-1);
		i++;
	}
	return (0);
}
