/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:13:43 by hamad             #+#    #+#             */
/*   Updated: 2024/10/16 22:15:42 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
	@brief		This function will dup2 to stdin(0), stdout(1) or both to = 2.
	@param	fd	This holds the file descriptors.
	@param	to	This accepts 3 values 0, 1, 2.
	@return		If duplication was successful 1 will be returned else -1.
*/
int	dup_pipes(int *fd, int to)
{
	if (!fd || to < 0)
		return (-1);
	if (to == 2)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0 || dup2(fd[0], STDIN_FILENO) < 0)
			return (-1);
		return (close_pipe(fd, to), 1);
	}
	if (to == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (-1);
		return (close_pipe(fd, to), 1);
	}
	if (to == 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (-1);
		return (close_pipe(fd, to), 1);
	}
	return (-1);
}

/**
 * @brief			This function will initialize all pipes up to size pipes.
 * @param	fd		This holds the number of pipelines needed.
 * @param	size	This holds the number of pipelines we have.
 * @return			Upon success 1; Failure -1.
 */

int	init_pipes(int fd[][2], size_t size)
{
	size_t	i;

	if (!fd)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (pipe(fd[i]) == -1)
			return (close_pipes(fd, size), -1);
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
void	close_pipes(int fd[][2], size_t	npipes)
{
	size_t	i;

	i = 0;
	while (i < npipes)
	{
		if (fd[i][0] >= 0)
			close(fd[i][0]);
		if (fd[i][1] >= 0)
			close(fd[i][1]);
		i++;
	}
}