/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truedeveloper <truedeveloper@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:52:29 by hamalmar          #+#    #+#             */
/*   Updated: 2024/08/20 14:27:28 by truedevelop      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	total_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

char	*copy_current_word(char const *s, unsigned int start, unsigned int end)
{
	unsigned int	i;
	char			*new_word;

	new_word = malloc(sizeof(char) * (end - start) + 1);
	if (new_word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		new_word[i] = s[start];
		i++;
		start++;
	}
	new_word[i] = '\0';
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			**new_s;

	i = 0;
	j = 0;
	k = 0;
	new_s = malloc(sizeof(char *) * (total_words(s, c) + 1));
	if (!s || !(new_s) || s[0] == '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			new_s[k++] = copy_current_word(s, j, i);
		}
		else
			i++;
	}
	new_s[k] = NULL;
	return (new_s);
}
