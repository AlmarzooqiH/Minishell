/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:16 by hamad             #+#    #+#             */
/*   Updated: 2024/11/06 17:28:11 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will count the number of redirections that are prese-
 * 			-nt within the command.
 * @param	command This holds the command that was passed.
 * @return	Will return the number of redirections within the command.
 */
size_t	count_redirections(char **command)
{
	size_t	n;
	size_t	i;

	if (!command)
		return (0);
	i = 0;
	n = 0;
	while (command[i] != NULL)
	{
	if (ft_strcmp(command[i], REDICERTION_TO_FILE) || ft_isprefix(command[i], REDICERTION_TO_FILE))
		n++;
	else if (ft_strcmp(command[i], REDIRECTION_TO_INPUT) || ft_isprefix(command[i], REDIRECTION_TO_INPUT))
		n++;
	else if (ft_strcmp(command[i], APPEND_REDIRECTION) || ft_isprefix(command[i], APPEND_REDIRECTION))
		n++;
	else if (ft_strcmp(command[i], HEREDOC_REDIRECTION) || ft_isprefix(command[i], HEREDOC_REDIRECTION))
		n++;
	}
	return (n);
}
/**
 * @brief	This function will process any rediection based on the user input.
 * @param	bdir	Binary/executable path.
 * @param	command	This will hold in the current command.
 * @param	fname	This will hold the filename(Can be NULL).
 * @param	re		This holds the type of redierction we got. If -1 this mean-
 * -s there are no redierections and will be processed normally.
 * @return Void.
*/
void	process_redirection(char **bdir, char **command, char *fname, int re, int (*fd)[2], int cpipe)
{
	if (re == e_redirection_to_file)
		return (redierct_to_file(bdir, command, fname, O_TRUNC, fd, cpipe));
	else if (re == e_redirection_to_input)
		return (redierct_to_input(bdir, command, fname, fd, cpipe));
	else if (re == e_append_redirection)
		return (redierct_to_file(bdir, command, fname, O_APPEND, fd, cpipe));
	else if (re == e_heredoc_redirection)
		return (heredoc_to_input(bdir, command, fname, fd, cpipe));
	else
		return (normal_process(bdir, command, NULL, fd, cpipe));
}
