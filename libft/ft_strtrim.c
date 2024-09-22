/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:51:10 by hamalmar          #+#    #+#             */
/*   Updated: 2024/09/21 12:58:08 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	int		len;
	char	*new_s;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1) - 1;
	while (end > begin && ft_strchr(set, s1[end]))
		end--;
	len = end - begin + 1;
	if (len <= 0)
		len = 0;
	new_s = ft_substr(s1, begin, len);
	if (!new_s)
		return (NULL);
	return (new_s);
}
