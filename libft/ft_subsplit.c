/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:59:20 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 20:53:40 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_subsplit(char **split, char *delimeter)
{
	size_t	i;
	size_t	size;
	char	**new_s;

	if (!split || !delimeter)
		return (NULL);
	i = 0;
	while (i < count_split(split))
	{
		if (ft_strcmp(split[i], delimeter))
			break ;
		i++;
	}
	new_s = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_s)
		return (NULL);
	size = i;
	i = 0;
	while (i < size)
	{
		new_s[i] = ft_strdup(split[i]);
		if (!new_s[i++])
			return (free_split(new_s), NULL);
	}
	return (new_s[i] = NULL, new_s);
}
