/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:07:54 by hamad             #+#    #+#             */
/*   Updated: 2025/01/13 16:16:07 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_split(char **split)
{
	char	**dup;
	int		i;

	if (!split || !split[0])
		return (NULL);
	i = count_split(split);
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (split[i])
	{
		dup[i] = ft_strdup(split[i]);
		if (!dup[i])
			return (free_split(dup), NULL);
		i++;
	}
	return (dup[i] = NULL, dup);
}
