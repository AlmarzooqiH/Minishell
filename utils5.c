/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:33:51 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 18:56:11 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_end(char *command, char split, int *j)
{
	while (command[*j] && command[*j] != split)
	{
		if (is_quote(command[*j]))
		{
			(*j)++;
			while (command[*j] && !is_quote(command[*j]))
				(*j)++;
			if (command[*j])
				(*j)++;
		}
		else
			(*j)++;
	}
}

/**
 * @brief This function will calculate the number of tokens.
 * @param temp The command.
 * @return size_t The number of tokens.
*/
size_t	get_ntokens(char *temp)
{
	size_t	tokens;
	size_t	i;

	if (!temp || !temp[0])
		return (0);
	i = ft_skipspace(temp);
	tokens = 0;
	while (i < ft_strlen(temp) && temp[i] != '\0')
	{
		if (is_quote(temp[i]))
		{
			i++;
			while (temp[i] && !is_quote(temp[i]))
				i++;
			i++;
		}
		else
		{
			while (i < ft_strlen(temp) && !ft_isspace(temp[i]))
				i++;
		}
		i += ft_skipspace((temp + i));
		tokens++;
	}
	return (tokens);
}

size_t	get_token_length(char *temp, size_t i)
{
	char	qoute;

	if (is_quote(temp[i]))
	{
		qoute = temp[i];
		i++;
		while (temp[i] && temp[i] != qoute)
			i++;
		return (i + 1);
	}
	while (temp[i] && !ft_isspace(temp[i]))
		i++;
	return (i);
}

void	extract_tokens(char **new_s, char *temp)
{
	size_t	i;
	size_t	k;
	size_t	start;

	i = 0;
	k = 0;
	start = 0;
	while (temp[i])
	{
		i += ft_skipspace(temp + i);
		if (!temp[i])
			break ;
		start = i;
		i = get_token_length(temp, i);
		new_s[k++] = ft_substr(temp, start, i - start);
	}
	new_s[k] = NULL;
}

char	**get_command(char *temp)
{
	char	**new_s;

	new_s = (char **)ft_calloc(sizeof(char *), get_ntokens(temp) + 1);
	if (!new_s)
		return (NULL);
	extract_tokens(new_s, temp);
	return (new_s);
}
