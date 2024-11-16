/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:31:03 by hamad             #+#    #+#             */
/*   Updated: 2024/11/16 17:15:26 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This command will check if the command in in bash syntax or not e.g.:
 * <filein command or <<delimeter command.
 * @param	command	This holds the command we want to check.
 * @return 1 if the command is in bash syntax, 0 otherwise.
 */
int	is_bashsyntax(char **command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command[0], APPEND_REDIRECTION) || ft_isprefix(command[0], APPEND_REDIRECTION))
		return (1);
	else if (ft_strcmp(command[0], HEREDOC_REDIRECTION) || ft_isprefix(command[0], HEREDOC_REDIRECTION))
		return (1);
	else if (ft_strcmp(command[0], REDICERTION_TO_FILE) || ft_isprefix(command[0], REDICERTION_TO_FILE))
		return (1);
	else if (ft_strcmp(command[0], REDIRECTION_TO_INPUT) || ft_isprefix(command[0], REDIRECTION_TO_INPUT))
		return (1);
	return (0);
}
/**
 * @brief This function will check if the current input is a redirection but a-
 * -lone like this: cat < filein or < file in cat -e
 * @param	s	This holds the current string we want to check.
 * @return	1 if the input is a redirection alone, 0 otherwise.
 */
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
void	process_alone(char **bdir, char **command, size_t *i, int redirection, int *cflag, int (*fd)[2], size_t *cpipe)
{
	size_t	j;
	char	**sub_command;

	*i = *i + 1;
	j = *i;
	while (command[j] != NULL && !(is_redirection(command[j]) >= 0))
		j++;
	if (*cflag)
		sub_command = trim_command(ft_subnsplit(command, (*i) + 1, j));
	if (*cflag && !sub_command)
		return (perror("Failed to get subcommand."));
	process_redirection(bdir, sub_command, command[*i], redirection, cflag, fd, cpipe);
	if (*cflag && sub_command)
		free_split(1, sub_command);
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
void	process_not_alone(char **bdir, char **command, size_t *i, int redirection, int *cflag, int (*fd)[2], size_t *cpipe)
{
	size_t	j;
	char	**sub_command;
	char	*fname;

	fname = get_filename(command[(*i)], redirection);
	if (!fname)
		return (perror("Invalid file name"));
	j = *i + 1;
	while (command[j] != NULL && !(is_redirection(command[j]) >= 0))
		j++;
	if (*cflag)
		sub_command = trim_command(ft_subnsplit(command, (*i) + 1, j));
	if (*cflag && !sub_command)
		return (perror("Failed to get subcommand."));
	process_redirection(bdir, sub_command, fname, redirection, cflag, fd, cpipe);
	if (*cflag && sub_command)
		free_split(1, sub_command);
	*i = j;
	free(fname);
}

void	process_bash(char **bdir, char **command, int (*fd)[2], size_t *cpipe, size_t npipes)
{
	size_t	i;
	int		redirection;
	int		cflag;

	if (!command)
		return ;
	i = 0;
	cflag = 1;
	(void)npipes;
	while (command[i] != NULL && i < count_split(command) && *cpipe < npipes)
	{
		redirection = is_redirection(command[i]);
		if (redirection >= 0 && is_alone(command[i]))
			process_alone(bdir, command, &i, redirection, &cflag, fd, cpipe);
		else if (redirection >= 0 && !is_alone(command[i]))
			process_not_alone(bdir, command, &i, redirection, &cflag, fd, cpipe);
	}
}
