/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:37:31 by hamad             #+#    #+#             */
/*   Updated: 2024/12/25 16:58:01 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will free the memory allocated by the cmds struct.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	free_cmds2(t_commands *cmds)
{
	cmds->a = 0;
	cmds->t = 0;
	cmds->r = 0;
}

/**
 * @brief	This function will free the memory allocated by the cmds struct.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	free_cmds(t_commands *cmds)
{
	close_files(cmds);
	if (cmds->bpath)
		free_split(cmds->bpath);
	if (cmds->cmds)
		free_tokens(cmds->cmds, cmds->nscmds);
	if (cmds->files)
		free_split(cmds->files);
	if (cmds->rd)
		free_arri(cmds->rd);
	if (cmds->is_bash)
		free(cmds->is_bash);
	if (cmds->nscmds > 1 && cmds->p)
		free(cmds->p);
	cmds->nscmds = 0;
	cmds->npipes = 0;
	cmds->nre = 0;
	cmds->cp = 0;
	cmds->cc = 0;
	cmds->cf = 0;
	cmds->cr = 0;
	cmds->hdp = -1;
	cmds->rtip = -1;
	cmds->bfdp = 0;
	cmds->efdp = -1;
	free_cmds2(cmds);
}

void	init3(t_commands *cmds)
{
	cmds->cr = 0;
	cmds->bfdp = 0;
	cmds->efdp = -1;
	cmds->hdp = -1;
	cmds->rtip = -1;
	cmds->a = O_CREAT | O_RDWR | O_APPEND;
	cmds->t = O_CREAT | O_RDWR | O_TRUNC;
	cmds->r = O_RDONLY;
}

void	init2(t_commands *cmds)
{
	set_isbash(cmds);
	cmds->nre = get_total_rediractions(cmds->cmds);
	if (cmds->nre > 0)
	{
		cmds->rd = (int **)malloc(sizeof(int *) * (cmds->nre));
		cmds->files = (char **)malloc(sizeof(char *) * (cmds->nre + 1));
		if (!cmds->rd || !cmds->files)
			return (free_cmds(cmds), perror("Failed to malloc redir/files"));
		set_redirectons(cmds);
		set_files(cmds);
		if (!cmds->rd || !cmds->files)
			return (free_cmds(cmds), perror("Failed to get redir/files"));
		cmds->fd = malloc(sizeof(int) * (cmds->nre));
		if (!cmds->fd)
			return (free_cmds(cmds), perror("Failled to malloc fd"));
	}
	else
	{
		cmds->rd = NULL;
		cmds->files = NULL;
	}
	cmds->cp = 0;
	cmds->cc = 0;
	cmds->cf = 0;
	init3(cmds);
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
	if (init_pipes(&cmds->p, cmds->nscmds) == -1)
		return (free_cmds(cmds), perror("Failed to init pipes."));
	cmds->npipes = cmds->nscmds - 1;
	cmds->cfd = 0;
	init2(cmds);
}
