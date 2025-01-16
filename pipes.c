/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:13:43 by hamad             #+#    #+#             */
/*   Updated: 2025/01/15 20:00:21 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will set the closed file descriptors to -1 after being
 * used and closed.
 * @param fd This holds the file descriptors.
 * @param	which	0 will close the read end.
 * @param	which	1 will close the write end.
 * @param	which	2 will close both ends.
 * @return			Void. 
*/
void	set_fds(int *fd, int which)
{
	if (which == 2)
	{
		fd[0] = -1;
		fd[1] = -1;
	}
	else if (which == 0)
		fd[0] = -1;
	else if (which == 1)
		fd[1] = -1;
}

/**
	@brief			This function will close the pipeline between the processes.
	@param	fd		This will hold the file descriptors.
	@param	which	0 will close the read end.
	@param	which	1 will close the write end.
	@param	which	2 will close both ends.
	@return			Void.
*/
void	cp(int *fd, int which)
{
	if (!fd)
		return ;
	if (which == 2)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		if (fd[1] >= 0)
			close(fd[1]);
	}
	else if (which == 0)
	{
		if (fd[0] >= 0)
			close(fd[0]);
	}
	else if (which == 1)
	{
		if (fd[1] >= 0)
			close(fd[1]);
	}
	set_fds(fd, which);
}

/**
	@brief		This function will dup2 to stdin(0), stdout(1) or (2) for stdi-
				-n for the current pipe, and stdout for the next pipe.
	@param		cmds	This holds the commands struct.
	@return		If duplication was successful 1 will be returned else -1.
*/
int	dup_pipes(t_commands *cmds)
{
	if (cmds->npipes == 1)
	{
		if ((cmds->cc == 0 && dup2(cmds->p[cmds->cp][1], SOUT) == -1) || (
			cmds->cc == 1 && cmds->p[cmds->cp][0] >= 0
		&& dup2(cmds->p[cmds->cp][0], SIN) == -1))
			return (gs_status(127, SET_STATUS), -1);
		return (cp(cmds->p[cmds->cp], 2), 1);
	}
	if (cmds->cc == 0)
	{
		if (dup2(cmds->p[cmds->cp][1], SOUT) == -1)
			return (gs_status(127, SET_STATUS), -1);
		return (cp(cmds->p[cmds->cp], 2), 1);
	}
	else if (cmds->cc == cmds->nscmds - 1)
	{
		if (dup2(cmds->p[cmds->cp][0], SIN) == -1)
			return (gs_status(127, SET_STATUS), -1);
		return (cp(cmds->p[cmds->cp], 2), 1);
	}
	if ((dup2(cmds->p[cmds->cp - 1][0], SIN) == -1) ||
			(dup2(cmds->p[cmds->cp][1], SOUT) == -1))
		return (gs_status(127, SET_STATUS), -1);
	return (cp(cmds->p[cmds->cp - 1], 2), cp(cmds->p[cmds->cp], 2), 1);
}

/**
 * @brief			This function will initialize all pipes up to size pipes.
 * @param	fd		This holds the number of pipelines needed.
 * @param	clen	This holds the length of the commands.
 * @return (Upon success 1); Failure -1.
 */
int	init_pipes(int (**fd)[2], int clen)
{
	int	i;

	if (clen == 1)
		return (*fd = NULL, 1);
	*fd = malloc(sizeof(int [2]) * (clen - 1));
	if (!*fd)
		return (-1);
	i = 0;
	while (i < (clen - 1))
	{
		if (pipe((*fd)[i]) < 0)
			return (cps(*fd, (clen - 1)), -1);
		i++;
	}
	return (1);
}

/**
	@brief			This function will close the pipeline between the processes.
	@param	fd		This will hold the pipelines.
	@param	npipes	This holds the number of pipelines that got.
	@return			Void.
*/
void	cps(int (*fd)[2], size_t npipes)
{
	size_t	i;

	if (!fd)
		return ;
	i = 0;
	while (i < npipes)
	{
		if (fd[i][0] >= 0)
			close(fd[i][0]);
		if (fd[i][1] >= 0)
			close(fd[i][1]);
		i++;
	}
	free(fd);
	fd = NULL;
}
