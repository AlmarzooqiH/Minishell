/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:18:31 by hamalmar          #+#    #+#             */
/*   Updated: 2024/06/30 10:33:42 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_format(char format, va_list *arg)
{
	int	len;
	int	c;

	if (!format)
		return (0);
	len = 0;
	if (format == 's')
		len += ft_print_str((va_arg(*arg, char *)));
	else if (format == 'c')
	{
		c = va_arg(*arg, int);
		len += write(1, &c, 1);
	}
	else if (format == 'd' || format == 'i')
		len += ft_print_number(va_arg(*arg, int));
	else if (format == 'u')
		len += ft_print_unsigned_num(va_arg(*arg, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_num_n_hex(va_arg(*arg, unsigned int), format);
	else if (format == 'p')
		len += ft_print_address(va_arg(*arg, void *));
	else if (format == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_characters;

	if (!format)
		return (0);
	va_start(args, format);
	total_characters = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			total_characters += check_format(*format, &args);
			format++;
		}
		else
		{
			total_characters += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (total_characters);
}
