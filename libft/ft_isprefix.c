/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprefix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:52:26 by hamad             #+#    #+#             */
/*   Updated: 2024/11/08 19:01:17 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprefix(const char *s1, const char *prefix)
{
	size_t	i;

	if (!s1 || !prefix)
		return (0);
	i = 0;
	while (s1[i] != '\0'&& prefix[i] != '\0' && prefix[i] == s1[i])
		i++;
	return (!prefix[i]);
}
