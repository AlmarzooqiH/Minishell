/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/12/19 17:09:13 by hamad            ###   ########.fr       */
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
 * @brief This function will create and open files and assign file descriptors
 * to cmds->fd[position of the fd].
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	create_files(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < count_tokens(cmds->cmds[cmds->cc]))
	{
		if (cmds->rd[cmds->cc][i] == e_rtf)
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], TRUNC, PERMS);
		else if (cmds->rd[cmds->cc][i] == e_rti && !check_file(cmds))
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], RD , PERMS);
		else if (cmds->rd[cmds->cc][i] == e_ar)
			cmds->fd[cmds->cfd] = open(cmds->files[cmds->cf], APPEND, PERMS);
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
		cmds->cf++;
		cmds->cfd++;
		cmds->cr = i;
		cmds->efdp = cmds->cfd;
	}
}

/**
 * @brief This function will process the redirections.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	process_redir(t_commands *cmds)
{
	int		i;
	char	**scmd;

	create_files(cmds);
	scmd = extract_command(cmds);
	if (!scmd)
		return (perror("Failed to extract the command"), exit(EF));
	if (cmds->hdp >= 0 && process_heredoc(cmds))
	{
		cmds->rd[cmds->cc][cmds->hdp] = open(TEMP_FILE, O_RDONLY, PERMS);
		if (dup2(cmds->rd[cmds->cc][cmds->hdp], SIN) == -1)
			return (perror("Failed to dup2(hdr, SIN)"), exit(EF));
	}
	if (cmds->rtip >= 0 && dup2(cmds->fd[cmds->rtip], SIN) == -1)
		return (perror("Failed to dup2(rtip, SIN)"), exit(EF));
	if (cmds->rd[cmds->cc][cmds->cr - 1] == e_rtf
		|| cmds->rd[cmds->cc][cmds->cr - 1] == e_ar)
	{
		if (dup2(cmds->fd[cmds->cfd - 1], SOUT) == -1)
			return (perror("Failed to dup2(rtf or rti, SOUT)"), exit(EF));
	}
	i = 0;
	while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
	return (close_files(cmds), free_split(scmd));
}	
