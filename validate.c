/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:48 by hamad             #+#    #+#             */
/*   Updated: 2025/01/01 20:45:19 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		return (perror("Failed to malloc commands"), 1);
	get_tokens(command, tokens, '|');
	i = 0;
	while (i < has_pipe(command))
	{
		j = 0;
		while (j < count_tokens(tokens[i]))
		{
			j++;
		}
		i++;
	}
	free_tokens(tokens, has_pipe(command));
	return (0);
}
