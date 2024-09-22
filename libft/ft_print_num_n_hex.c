/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_n_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:07:18 by hamalmar          #+#    #+#             */
/*   Updated: 2024/06/30 10:33:53 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_num_n_hex(unsigned int n, char casing)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	else if (casing == 'x')
	{
		if (n / 16 == 0)
			return (write(1, &LOWER[n % 16], 1));
		count += (ft_print_num_n_hex((n / 16), 'x') + write(1, &LOWER[n % 16],
					1));
	}
	else if (casing == 'X')
	{
		if (n / 16 == 0)
			return (write(1, &UPPER[n % 16], 1));
		count += (ft_print_num_n_hex((n / 16), 'X') + write(1, &UPPER[n % 16],
					1));
	}
	return (count);
}
