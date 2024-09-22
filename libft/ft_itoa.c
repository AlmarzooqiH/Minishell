/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:48:45 by hamalmar          #+#    #+#             */
/*   Updated: 2024/07/04 07:22:29 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_length(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	copy_num(int n, char *char_n, int size)
{
	int	i;

	if (n < 0)
	{
		n *= -1;
		char_n[0] = '-';
	}
	if (n == 0)
		*char_n = '0';
	i = size - 1;
	while (n != 0)
	{
		char_n[i] = (n % 10) + 48;
		i--;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*char_n;
	int		n_len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		n_len = (sizeof(char) * int_length(n * -1)) + 2;
	else
		n_len = (sizeof(char) * int_length(n)) + 1;
	char_n = malloc(n_len);
	if (!char_n)
		return (NULL);
	char_n[n_len - 1] = 0;
	copy_num(n, char_n, (n_len - 1));
	return (char_n);
}
