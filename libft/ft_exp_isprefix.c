/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp_isprefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 07:59:38 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/28 08:04:33 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exp_isprefix(const char *s1, const char *prefix)
{
	size_t	i;

	if (!s1 || !prefix || ft_strlen(s1) < ft_strlen(prefix))
		return (0);
	i = 0;
	while (s1[i] != '\0' && prefix[i] != '\0' && prefix[i] == s1[i])
		i++;
	return (!prefix[i] && (s1[i] == '\0' || !ft_isalnum(s1[i])));
}
