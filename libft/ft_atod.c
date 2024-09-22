/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:29:23 by hamad             #+#    #+#             */
/*   Updated: 2024/09/19 20:18:09 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *s)
{
	double	out;
	double	decimal_place;
	int		sign;
	size_t	i;	

	out = ft_atoi(s);
	decimal_place = 0.1;
	i = ft_skipspace(s);
	sign = 1;
	if (s[i] == '-')
	{
		out = -out;
		i++;
		sign = -sign;
	}
	while (s[i] == '+' || ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
		i++;
	while (ft_isdigit(s[i]))
	{
		out = out + (s[i++] - '0') * decimal_place;
		decimal_place /= 10;
	}
	return (out * sign);
}
