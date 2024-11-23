/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subnsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:58:43 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 20:53:46 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_subnsplit(char **split, size_t start, size_t end)
{
	size_t	i;
	char	**new_s;

	if (!split || start > end)
		return (NULL);
	if (end >= count_split(split))
		new_s = (char **) malloc(sizeof(char *) * ((count_split(split) - start) \
								+ 1));
	else
		new_s = (char **) malloc(sizeof(char *) * ((end - start) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (start < count_split(split) && start < end)
	{
		new_s[i] = ft_strdup(split[start]);
		if (!new_s[i])
			return (free_split(new_s), NULL);
		i++;
		start++;
	}
	return (new_s[i] = NULL, new_s);
}
