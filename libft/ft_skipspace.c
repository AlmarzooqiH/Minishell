/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:34:01 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 18:57:50 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_skipspace(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}
