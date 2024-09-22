/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:06:28 by hamalmar          #+#    #+#             */
/*   Updated: 2024/06/30 10:35:09 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_number(int n)
{
	char	current_digit;

	if (n == -2147483648)
	{
		return (write(1, "-2147483648", 11));
	}
	if (n < 0)
		return (write(1, "-", 1) + ft_print_number(-n));
	if (n >= 0 && n <= 9)
	{
		current_digit = n + '0';
		return (write(1, &current_digit, 1));
	}
	current_digit = (n % 10) + '0';
	return (ft_print_number(n / 10) + write(1, &current_digit, 1));
}
