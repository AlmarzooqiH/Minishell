/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:48 by hamad             #+#    #+#             */
/*   Updated: 2025/01/14 15:52:25 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @name Check if file exist.
 * @brief This function will check if the file exist or not.
 * @param tokens This will contain the file name.
 * @return 1 if the file exist, 0 otherwise.
 */
int	cife(char ***tokens, int *i, int *j)
{
	char	*file;
	int		redirection_type;

	redirection_type = is_redirection(tokens[*i][*j]);
	if (is_alone(tokens[*i][*j]))
	{
		(*j)++;
		if (!tokens[*i][*j])
			return (perror("No file/delimeter after redirection"), 0);
		file = ft_strdup(tokens[*i][*j]);
	}
	else
		file = gfn(tokens[*i][*j], redirection_type);
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
 * @name Check if empty command.
 * @brief This function will check if the current command is empty or not.
 * @param tokens This will contain the tokens.
 * @param i This will contain the index of the token.
 * @param npipes This will contain the number of pipes.
 */
int	ciec(char ***tokens, int i, int npipes)
{
	int		j;
	int		k;
	char	**tmp;

	(void)npipes;
	(void)j;
	tmp = trim_command(ft_dup_split(tokens[i]));
	if (!tmp || tmp[0] == NULL)
		return (perror("Empty Command"), 0);
	j = 0;
	k = 0;
	while (j < count_tokens(tokens[i]) && tmp[j] != NULL)
	{
		if (tmp[j][0] == '\0')
			k++;
		j++;
	}
	if (k == count_tokens(tokens[i]))
		return (perror("Empty Command"), free_split(tmp), 0);
	return (free_split(tmp), 1);
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
		if (!ciec(tokens, i, has_pipe(command)))
			return (free_tokens(tokens, has_pipe(command)), 0);
		j = 0;
		while (j < count_tokens(tokens[i]))
		{
			if (is_redirection(tokens[i][j]) >= 0 && !cife(tokens, &i, &j))
				return (free_tokens(tokens, has_pipe(command)), 0);
			j++;
		}
		i++;
	}
	return (free_tokens(tokens, has_pipe(command)), 1);
}
