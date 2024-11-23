/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 17:25:57 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will check if the passed command contained any redir-
 * 			-ection operators('>', '<', '>>', '<<').
 * @param	commad		This will hold the passed in command.
 * @return	-1 if there is no redirections
 * @return	e_redirection_to_file if the command had '>'.
 * @return	e_redirection_to_input if the command had '<'.
 * @return	e_append_redirection if the command had '>>'.
 * @return	e_heredoc_redirection if the command had '<<'.
 */
int	is_redirection(char *command)
{
	if (ft_strcmp(command, APPEND_REDIRECTION) || ft_isprefix(command, APPEND_REDIRECTION))
		return (e_append_redirection);
	else if (ft_strcmp(command, HEREDOC_REDIRECTION) || ft_isprefix(command, HEREDOC_REDIRECTION))
		return (e_heredoc_redirection);
	else if (ft_strcmp(command, REDICERTION_TO_FILE) || ft_isprefix(command, REDICERTION_TO_FILE))
		return (e_redirection_to_file);
	else if (ft_strcmp(command, REDIRECTION_TO_INPUT) || ft_isprefix(command, REDIRECTION_TO_INPUT))
		return (e_redirection_to_input);
	return (-1);
}
