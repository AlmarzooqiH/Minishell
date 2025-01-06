/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:48 by hamad             #+#    #+#             */
/*   Updated: 2025/01/07 03:38:13 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @name Check if file exist.
 * @brief This function will check if the file exist or not.
 * @param token This will contain the file name.
 * @return 1 if the file exist, 0 otherwise.
 */
int	cife(char ***token, int *i, int *j)
{
	char	*file;
	int		redirection_type;

	redirection_type = is_redirection(token[*i][*j]);
	if (is_alone(token[*i][*j]))
	{
		(*j)++;
		if (!token[*i][*j])
			return (perror("No file/delimeter after redirection"), 0);
		file = ft_strdup(token[*i][*j]);
	}
	else
		file = gfn(token[*i][*j], redirection_type);
	if (!file)
		return (perror("Failed to get file/delimeter"), 0);
	if (redirection_type == e_rti)
	{
		if (access(file, F_OK) == -1)
			return (perror("File does not exist"), 0);
	}
	else if (redirection_type == e_hdr && is_redirection(file) >= 0)
		return (perror("Invalid delimeter"), 0);
	if (file)
		free(file);
	return (1);
}

/**
 * @brief This function will validate the passed in command.
 * @param command The command to validate.
 * @return 1 if the command is valid, 0 otherwise.
 */
int	validate_command(char *command)
{
	int		i;
	int		j;
	char	***tokens;

	tokens = (char ***)malloc(sizeof(char **) * (has_pipe(command) + 1));
	if (!tokens)
		return (perror("Failed to malloc commands"), 0);
	get_tokens(command, tokens, '|');
	if (!tokens || !tokens[0] || !tokens[0][0])
		return (perror("Failed to get tokens"), 0);
	i = 0;
	while (i < has_pipe(command))
	{
		j = 0;
		while (j < count_tokens(tokens[i]))
		{
			if (is_redirection(tokens[i][j]) >= 0 && !cife(tokens, &i, &j))
				return (free_tokens(tokens, has_pipe(command)), 0);
			j++;
		}
		i++;
	}
	free_tokens(tokens, has_pipe(command));
	return (1);
}
