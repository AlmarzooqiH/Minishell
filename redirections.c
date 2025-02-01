/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 19:12:38 by mthodi           ###   ########.fr       */
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
	if (ft_strcmp(command, APPEND_REDIRECTION)
		|| ft_isprefix(command, APPEND_REDIRECTION))
		return (e_ar);
	else if (ft_strcmp(command, HEREDOC_REDIRECTION)
		|| ft_isprefix(command, HEREDOC_REDIRECTION))
		return (e_hdr);
	else if (ft_strcmp(command, REDICERTION_TO_FILE)
		|| ft_isprefix(command, REDICERTION_TO_FILE))
		return (e_rtf);
	else if (ft_strcmp(command, REDIRECTION_TO_INPUT)
		|| ft_isprefix(command, REDIRECTION_TO_INPUT))
		return (e_rti);
	return (-1);
}

/**
 * @brief This function will check if we have opened the files successfully.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	check_if_success(t_commands *cmds)
{
	int	i;

	i = cmds->bfdp;
	while (i < cmds->efdp)
	{
		if (cmds->fd[i] < 0)
			return (gs_status(GET_STATUS, SET_STATUS),
				perror("Failed to open file"),
				free_tings(cmds, NULL, NULL), exit(EF));
		i++;
	}
	gs_status(SET_STATUS, SET_STATUS);
}

/**
 * @brief This function will increment and assign the struct members.
 * @return Void.
 */
void	increment(t_commands *cmds, int i)
{
	cmds->cf++;
	cmds->cfd++;
	cmds->cr = i;
	cmds->efdp = cmds->cfd;
}

/**
 * @brief This function will create and open files and assign file descriptors
 * to cmds->fd[position of the fd].
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	create_files(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < count_tokens(cmds->c[cmds->cc]))
	{
		if (cmds->rd[cmds->cc][i] == e_rtf)
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], cmds->t, PERMS);
		else if (cmds->rd[cmds->cc][i] == e_rti && !check_file(cmds))
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], cmds->r, PERMS);
		else if (cmds->rd[cmds->cc][i] == e_ar)
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], cmds->a, PERMS);
		else if (cmds->rd[cmds->cc][i] == e_hdr)
			cmds->hdp = cmds->cf;
		else if (cmds->rd[cmds->cc][i] == -1)
		{
			i++;
			continue ;
		}
		if (cmds->rd[cmds->cc][i] == e_rti)
			cmds->rtip = cmds->cfd;
		i++;
		increment(cmds, i);
	}
	check_if_success(cmds);
}

/**
 * @brief This function will process the redirections.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	predir(t_commands *cmds)
{
	create_files(cmds);
	if (cmds->hdp >= 0 && process_heredoc(cmds))
		dup_heredoc(cmds);
	if (cmds->p && dup_pipes(cmds) == -1)
		return (perror("Failed to dup pipes"), exit(EF));
	if (cmds->rtip >= 0 && dup2(cmds->fd[cmds->rtip], SIN) == -1)
		return (perror("Failed to dup2(rtip, SIN)"), exit(EF));
	if (cmds->rd[cmds->cc][cmds->cr - 1] == e_rtf
		|| cmds->rd[cmds->cc][cmds->cr - 1] == e_ar)
	{
		if (dup2(cmds->fd[cmds->cfd - 1], SOUT) == -1)
			return (perror("Failed to dup2(rtf or ar, SOUT)"), exit(EF));
	}
	child_functions(cmds);
	close_files(cmds);
}
