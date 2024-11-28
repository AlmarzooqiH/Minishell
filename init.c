/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:37:31 by hamad             #+#    #+#             */
/*   Updated: 2024/11/25 22:34:57 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will free the memory allocated by the cmds struct.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	free_cmds(t_commands *cmds)
{
	if (cmds->enviorment)
		free(cmds->enviorment);
	if (cmds->bpath)
		free_split(cmds->bpath);
	if (cmds->cmds)
		free_tokens(cmds->cmds, cmds->nscmds);
	if (cmds->files)
		free_split(cmds->files);
	if (cmds->redir)
		free_arri(cmds->redir);
	if (cmds->is_bash)
		free(cmds->is_bash);
	if (cmds->nscmds > 1 && cmds->fd)
		close_pipes(cmds->fd, (cmds->nscmds));
	cmds->nscmds = 0;
	cmds->npipes = 0;
	cmds->nredir = 0;
	cmds->cpipe = 0;
	cmds->ccmd = 0;
	cmds->cfile = 0;
	cmds->cred = 0;
}

void	init2(t_commands *cmds)
{
	set_isbash(cmds);
	cmds->nredir = get_total_rediractions(cmds->cmds);
	if (cmds->nredir > 0)
	{
		cmds->redir = (int **)malloc(sizeof(int *) * (cmds->nredir));
		cmds->files = (char **)malloc(sizeof(char *) * (cmds->nredir + 1));
		if (!cmds->redir || !cmds->files)
			return (free_cmds(cmds), perror("Failed to malloc redir/files"));
		set_redirectons(cmds);
		set_files(cmds);
		if (!cmds->redir || !cmds->files)
			return (free_cmds(cmds), perror("Failed to get redir/files"));
	}
	else
	{
		cmds->redir = NULL;
		cmds->files = NULL;
	}
	cmds->cpipe = 0;
	cmds->ccmd = 0;
	cmds->cfile = 0;
	cmds->cred = 0;
}
void	init(t_commands *cmds, const char *command)
{
	if (!cmds)
		return ;
	cmds->enviorment = getenv("PATH");
	if (!cmds->enviorment)
		return (free_cmds(cmds), perror("Failed to get the PATH variable"));
	cmds->bpath = ft_split(cmds->enviorment, ':');
	if (!cmds->bpath)
		return (free_cmds(cmds), perror("Failed to split the PATH variable"));
	cmds->nscmds = has_pipe((char *)command);
	cmds->cmds = (char ***)malloc(sizeof(char **) * (cmds->nscmds + 1));
	if (!cmds->cmds)
		return (free_cmds(cmds), perror("Failed to malloc commands"));
	get_tokens((char *)command, cmds->cmds, '|');
	if (!cmds->cmds || !cmds->cmds[0])
		return (free_cmds(cmds), perror("Failed to tokenize the input"));
	cmds->is_bash = (int (*))malloc(sizeof(int) * (cmds->nscmds));
	if (!cmds->is_bash)
		return (free_cmds(cmds), perror("Failed to malloc is_bash"));
	if (init_pipes(&cmds->fd, cmds->nscmds) == -1)
		return (free_cmds(cmds), perror("Failed to init pipes."));
	cmds->npipes = cmds->nscmds - 1;
	init2(cmds);
}
