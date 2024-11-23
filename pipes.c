/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:13:43 by hamad             #+#    #+#             */
/*   Updated: 2024/11/24 02:01:47 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
	@brief			This function will close the pipeline between the processes.
	@param	fd		This will hold the file descriptors.
	@param	which	0 will close the read end.
	@param	which	1 will close the write end.
	@param	which	2 will close both ends.
	@return			Void.
*/
void	close_pipe(int *fd, int which)
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
}

/**
	@brief		This function will dup2 to stdin(0), stdout(1) or (2) for stdi-
				-n for the current pipe, and stdout for the next pipe.
	@param	fd	This holds the file descriptors.
	@param	to	This accepts 3 values 0, 1, 2.
	@return		If duplication was successful 1 will be returned else -1.
*/
int	dup_pipes(int (*fd)[2], size_t cpipe, int to)
{
	if (!fd || to < 0)
		return (-1);
	if (to == 2)
	{
		if (dup2(fd[cpipe][0], SIN) < 0 || dup2(fd[cpipe + 1][1], SOUT) < 0)
			return (-1);
		return (close_pipe(fd[cpipe], 0), close_pipe(fd[cpipe + 1], 1), 1);
	}
	if (to == 0)
	{
		if (dup2(fd[cpipe][0], SIN) < 0)
			return (-1);
		return (close_pipe(fd[cpipe], to), 1);
	}
	if (to == 1)
	{
		if (dup2(fd[cpipe][1], SOUT) < 0)
			return (-1);
		return (close_pipe(fd[cpipe], to), 1);
	}
	return (-1);
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
			return (close_pipes(*fd, (clen - 1)), -1);
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
void	close_pipes(int (*fd)[2], size_t npipes)
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
}
