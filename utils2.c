/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:23:52 by hamad             #+#    #+#             */
/*   Updated: 2024/10/07 14:05:20 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
	@brief	This function will count the number of lines in stdout.
	@return	On success it will return the number of lines.
	@return	On failure it will return -1.
*/
long	count_lines(void)
{
	char	*s;
	int		fd;
	size_t	size;

	fd = open("out.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	size = 0;
	s = get_next_line(fd);
	while (s)
	{
		size++;
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	return (size);
}

/*
	@brief This function will split the commands into sub strings that will be
			stored in an array.
	@param	command		The commands that was passed in by the user.
	@param	tokens		Here is where the commands will be stored.
	@param	split		The delimeter that we want to use to split the tokens.
	@var	temp		This will temporaraly hold the substring.
	@var	temp_split	This will hold the tokens that we split from the temp.
	@var	i			Will iterate through the string.
	@var	j			Will store the end of the substring.
	@var	k			Will be the position for the tokens.
*/
void	get_tokens(char *command, char ***tokens, char split)
{
	char	*temp;
	char	**temp_split;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (command[i])
	{
		j = i;
		while (command[j] && command[j] != split)
			j++;
		temp = ft_substr(command, i, j - i);
		if (!temp)
			break ;
		temp_split = ft_split(temp, ' ');
		tokens[k++] = temp_split;
		free(temp);
		if (command[j] != '\0')
			i = j + 1;
		else
			i = j;
	}
	tokens[k] = NULL;
}

/*
	@brief				This function will free the tokens.
	@param	tokens		The tokens that we want to free.
	@param	n_tokens	The size of tokens param.
*/
void	free_tokens(char ***tokens, int n_tokens)
{
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		free_split(tokens[i]);
		i++;
	}
	free(tokens);
}
