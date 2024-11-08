/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:43:57 by hamad             #+#    #+#             */
/*   Updated: 2024/11/08 19:04:57 by hamalmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will extract the file name from the command.
 * @param	command	The command that contains the filename and redierction e.g.
 * 					<filename, we will substring it to filename only.
 * @param	redirection	This will tell us what redierction it is in.
 * @return	filename if successfull.
 * @return	NULL if failure.
 */
char *get_filename(char *command, int redirection)
{
	char	*filename;
	size_t	i;

	if (!command)
		return (NULL);
	i = 0;
	if (redirection == e_redirection_to_file)
		i = 1;
	else if (redirection == e_redirection_to_input)
		i = 1;
	else if (redirection == e_append_redirection)
		i = 2;
	else if (redirection == e_heredoc_redirection)
		i = 2;
	if (!i)
		return (NULL);
	filename = ft_substr(command, i, ft_strlen(command));
	if (!filename)
		return (NULL);
	return (filename);
}
