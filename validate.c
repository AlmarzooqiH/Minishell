/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:48 by hamad             #+#    #+#             */
/*   Updated: 2025/01/23 14:35:18 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Check if command has unclosed quotes
 * @param command The command string to check
 * @return 1 if quotes are properly closed or no quotes present, 0 otherwise
 */
int	check_quoted_command(char *command)
{
	int				i;
	t_quote_info	info;

	if (!command)
		return (0);
	init_quote_tracking(&info);
	i = skip_whitespace(command);
	while (command[i])
	{
		if (is_quote(command[i]))
			process_quote(command[i], &info, i);
		i++;
	}
	if (info.in_quotes)
	{
		printf("Error: Unclosed quote starting at position %d\n",
			info.start_pos);
		return (0);
	}
	return (1);
}

/**
 * @brief Check if a space at given position is within quotes
 * @param command Command string
 * @param pos Position of space to check
 * @return 1 if space is in quotes, 0 otherwise
 */
int	is_space_in_quotes(char *command, int pos)
{
	int				i;
	t_quote_info	info;

	if (!init_space_check(command, pos))
		return (0);
	init_quote_tracking(&info);
	i = 0;
	while (i < pos && command[i])
	{
		if (is_quote(command[i]))
			process_space_quote(command[i], &info);
		i++;
	}
	return (info.in_quotes);
}

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
			return (perror(NAR), gs_status(2, SET_STATUS), 0);
		file = ft_strdup(tokens[*i][*j]);
	}
	else
		file = gfn(tokens[*i][*j], redirection_type);
	if (!file)
		return (perror(FTFOD), 0);
	if (redirection_type == e_rti)
	{
		if (access(file, F_OK) == -1)
			return (perror(FDNE), gs_status(1, SET_STATUS), 0);
	}
	else if (redirection_type == e_hdr && is_redirection(file) >= 0)
		return (perror(I_D), gs_status(2, SET_STATUS), 0);
	if (file)
		free(file);
	return (1);
}

/**
 * @name Check if empty command.
 * @brief This function will check if the current command is empty or not.
 * @param tokens This will contain the tokens.
 * @param i This will contain the index of the token.
 * @js will contain the number of pipes.
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
 * @brief Validate the entire command
 * @param command The command to validate
 * @return 1 if valid, 0 if invalid
 */
int	validate_command(char *command)
{
	int		i;
	char	***tokens;

	if (!check_quoted_command(command))
		return (0);
	tokens = (char ***)malloc(sizeof(char **) * (has_pipe(command) + 1));
	if (!tokens)
		return (perror("Failed to malloc commands"), 0);
	get_tokens(command, tokens, '|');
	if (!tokens || !tokens[0] || !tokens[0][0])
		return (free_tokens(tokens, has_pipe(command)),
			perror("Failed to get tokens"), 0);
	i = 0;
	while (i < has_pipe(command))
	{
		if (!process_command_segment(tokens, i, has_pipe(command)))
			return (free_tokens(tokens, has_pipe(command)), 0);
		i++;
	}
	return (free_tokens(tokens, has_pipe(command)), 1);
}
