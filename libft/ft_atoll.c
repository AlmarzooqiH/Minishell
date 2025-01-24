/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:12:15 by hamad             #+#    #+#             */
/*   Updated: 2025/01/23 20:32:21 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*quote_is_bruh(char *str)
{
	if (*str == '\"' || *str == '\'')
		str++;
	return (str);
}

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	str = quote_is_bruh((char *)str);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	str = quote_is_bruh((char *)str);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (sign == -1)
		num = -num;
	return (num);
}
