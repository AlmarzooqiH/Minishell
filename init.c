/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:37:31 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 18:54:16 by hamad            ###   ########.fr       */
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
	cmds->nre = 0;
	cmds->cp = 0;
	cmds->cc = 0;
	cmds->cf = 0;
	cmds->cr = 0;
	cmds->hdp = -1;
	cmds->rtip = -1;
	cmds->bfdp = 0;
	cmds->efdp = -1;
	cmds->a = 0;
	cmds->t = 0;
	cmds->r = 0;
	cmds->npipes = 0;
	cmds->c = NULL;
	cmds->files = NULL;
	cmds->rd = NULL;
	cmds->is_bash = NULL;
	cmds->p = NULL;
	cmds->fd = NULL;
	cmds->previous_dir = NULL;
}

/**
 * @brief	This function will free the memory allocated by the cmds struct.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	free_cmds(t_commands *cmds)
{
	if (cmds->c)
		free_tokens(cmds->c, cmds->nscmds);
	if (cmds->files)
		free_split(cmds->files);
	if (cmds->rd)
		free_arri(cmds->rd, cmds->nscmds + 1);
	if (cmds->is_bash)
		free(cmds->is_bash);
	if (cmds->nscmds > 1 && cmds->p)
		cps(cmds->p, cmds->npipes);
	if (cmds->fd)
	{
		close_fd(cmds);
		free(cmds->fd);
	}
	if (cmds->previous_dir)
		free(cmds->previous_dir);
	cmds->nscmds = 0;
	cmds->npipes = 0;
	free_cmds2(cmds);
}

/**
 * @brief	This function will initialize the commands struct.
 * @param	cmds	This will holds the preprocessd command.
 * @return Void.
 */
void	init3(t_commands *cmds)
{
	cmds->cp = 0;
	cmds->cc = 0;
	cmds->cf = 0;
	cmds->cr = 0;
	cmds->bfdp = 0;
	cmds->efdp = -1;
	cmds->hdp = -1;
	cmds->rtip = -1;
	cmds->a = O_CREAT | O_RDWR | O_APPEND;
	cmds->t = O_CREAT | O_RDWR | O_TRUNC;
	cmds->r = O_RDONLY;
	cmds->previous_dir = NULL;
	cmds->bltin = 0;
}

/**
 * @brief This function will initialize the commands struct.
 * @param cmds This will holds the preprocessd command.
 * @return Void.
 */
void	init2(t_commands *cmds)
{
	set_isbash(cmds);
	cmds->nre = get_total_rediractions(cmds->c);
	if (cmds->nre > 0)
	{
		cmds->rd = (int **)ft_calloc(cmds->nscmds + 1, sizeof(int *));
		cmds->files = (char **)ft_calloc(cmds->nre + 1, sizeof(char *));
		if (!cmds->rd || !cmds->files)
			return (free_cmds(cmds), perror("Failed to malloc redir/files"));
		set_redirectons(cmds);
		set_files(cmds);
		if (!cmds->rd || !cmds->files)
			return (free_cmds(cmds), perror("Failed to get redir/files"));
		cmds->fd = (int *)ft_calloc(cmds->nre, sizeof(int));
		if (!cmds->fd)
			return (free_cmds(cmds), perror("Failled to malloc fd"));
	}
	else
	{
		cmds->rd = NULL;
		cmds->files = NULL;
		cmds->fd = NULL;
	}
	init3(cmds);
}

/**
 * @brief	This function will initialize the commands struct.
 * @param	cmds	This will holds the preprocessd command.
 * @param	command	This will holds the command that was passed.
 * @return Void.
 */
void	init(t_commands *cmds, const char *command)
{
	if (!cmds)
		return ;
	cmds->envp = gs_envp(NULL, GET_ENVP);
	if (!cmds->envp)
		return (free_cmds(cmds), perror("Failed to malloc envp"));
	cmds->nscmds = has_pipe((char *)command);
	cmds->c = (char ***)malloc(sizeof(char **) * (cmds->nscmds + 1));
	if (!cmds->c)
		return (free_cmds(cmds), perror("Failed to malloc commands"));
	get_tokens((char *)command, cmds->c, '|');
	if (!cmds->c || !cmds->c[0])
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
