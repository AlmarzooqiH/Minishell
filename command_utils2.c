/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:31:03 by hamad             #+#    #+#             */
/*   Updated: 2024/11/06 08:55:49 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_bashsyntax(char **command)
{
	if (!command)
		return (0);
	if (ft_isprefix(command[0], REDICERTION_TO_FILE))
		return (1);
	if (ft_isprefix(command[0], REDIRECTION_TO_INPUT))
		return (1);
	if (ft_isprefix(command[0], APPEND_REDIRECTION))
		return (1);
	if (ft_isprefix(command[0], HEREDOC_REDIRECTION))
		return (1);
	return (0);
}

int	is_alone(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, REDICERTION_TO_FILE))
		return (1);
	if (ft_strcmp(s, REDIRECTION_TO_INPUT))
		return (1);
	if (ft_strcmp(s, APPEND_REDIRECTION))
		return (1);
	if (ft_strcmp(s, HEREDOC_REDIRECTION))
		return (1);
	return (0);
}

/**
 * @brief This function will process a redirection with an input like this:
 * {redirection, filename(If there is), command, ...., NULL}.
 * @param	bdir	Binary/executable path.
 * @param	command	This will hold in the current command.
 * @param	i		This holds a pointer to the current position of the command
 * 					and it will be updated after finishing the processing.
 * @param	redirection	This holds the type of redirection which will be passe-
 * 						-ed to process_redirection.
 * @return	Void.
*/
void	process_alone(char **bdir, char **command, size_t *i, int redirection)
{
	size_t	j;
	char	**sub_command;

	*i = *i + 1;
	j = *i;
	while (command[j] != NULL && !(is_redirection(command[j]) >= 0))
		j++;
	sub_command = trim_command(ft_subnsplit(command, (*i) + 1, j - 1));
	if (!sub_command)
		return (perror("Failed to get subcommand."));
	process_redirection(bdir, sub_command, command[*i], redirection);
	free_split(sub_command);
	*i = j;
}

/**
 * @brief This function will process a redirection with an input like this:
 * {redirectionfilename(If there is a file name), command, ...., NULL}.
 * @param	bdir	Binary/executable path.
 * @param	command	This will hold in the current command.
 * @param	i		This holds a pointer to the current position of the command
 * 					and it will be updated after finishing the processing.
 * @param	redirection	This holds the type of redirection which will be passe-
 * 						-ed to process_redirection.
 * @return	Void.
*/
void	process_not_alone(char **bdir, char **command, size_t *i, int redirection)
{
	size_t	j;
	char	**sub_command;
	char	*fname;

	fname = get_filename(command[(*i)], redirection);
	if (!fname)
		return (perror("Invalid file name"));
	j = *i;
	while (command[j] != NULL && !(is_redirection(command[j]) >= 0))
		j++;
	sub_command = trim_command(ft_subnsplit(command, (*i) + 1, j - 1));
	if (!sub_command)
		return (perror("Failed to get subcommand."));
	process_redirection(bdir, sub_command, fname, redirection);
	free_split(sub_command);
	*i = j;
	free(fname);
}

void	process_bash(char **bdir, char **command, int fd[2])
{
	size_t	i;
	int		redirection;

	(void)fd;
	if (!command)
		return ;
	i = 0;
	while (command[i] != NULL && i < count_split(command))
	{
		redirection = is_redirection(command[i]);
		if (redirection >= 0 && is_alone(command[i]))
			process_alone(bdir, command, &i, redirection);
		else if (redirection >= 0 && !is_alone(command[i]))
			process_not_alone(bdir, command, &i, redirection);
		i++;
	}
}
