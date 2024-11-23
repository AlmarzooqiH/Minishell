/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:00:20 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 20:53:28 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_join_split(char **split1, char **split2)
{
	char	**new_split;
	size_t	i;

	if (!split1 || !split2)
		return (NULL);
	new_split = (char **)malloc(sizeof(char *) * (count_split(split1) +\
					count_split(split2) + 1));
	i = 0;
	while (new_split != NULL && *split1)
	{
		new_split[i] = ft_strdup(*split1);
		if (!new_split[i])
			return (free_split(new_split), NULL);
		split1++;
		i++;
	}
	while (new_split != NULL && *split2)
	{
		new_split[i] = ft_strdup(*split2);
		if (!new_split[i])
			return (free_split(new_split), NULL);
		split2++;
		i++;
	}
	return (new_split[i] = NULL, new_split);
}
