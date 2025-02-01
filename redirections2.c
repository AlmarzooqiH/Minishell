/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:16 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 19:13:05 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will count the number of redirections that are prese-
 * 			-nt within the command.
 * @param	command This holds the command that was passed.
 * @return	Will return the number of redirections within the command.
 */
int	count_redirections(char **command)
{
	int	n;
	int	i;

	if (!command)
		return (0);
	i = 0;
	n = 0;
	while (command[i] != NULL)
	{
		if (ft_strcmp(command[i], APPEND_REDIRECTION)
			|| ft_isprefix(command[i], APPEND_REDIRECTION))
			n++;
		else if (ft_strcmp(command[i], HEREDOC_REDIRECTION)
			|| ft_isprefix(command[i], HEREDOC_REDIRECTION))
			n++;
		else if (ft_strcmp(command[i], REDICERTION_TO_FILE)
			|| ft_isprefix(command[i], REDICERTION_TO_FILE))
			n++;
		else if (ft_strcmp(command[i], REDIRECTION_TO_INPUT)
			|| ft_isprefix(command[i], REDIRECTION_TO_INPUT))
			n++;
		i++;
	}
	return (n);
}

/**
 * @brief This function will count how many redierctions we got inside the com-
 * -mands.
 * @param	commands	This holds the commands that was passed.
 * @return	Will return the total number of redierctions.
*/
int	get_total_rediractions(char ***commands)
{
	int	i;
	int	total;

	if (!commands || !commands[0])
		return (0);
	i = 0;
	total = 0;
	while (commands[i] != NULL)
		total += count_redirections(commands[i++]);
	return (total);
}

/**
 * @brief This function will closed opened files of the current command.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	close_files(t_commands *cmds)
{
	int	i;

	if (!cmds->fd || !cmds->rd)
		return ;
	i = cmds->bfdp;
	if (access(TEMP_FILE, F_OK) == 0)
	{
		unlink(TEMP_FILE);
		close(cmds->rd[cmds->cc][cmds->hdp]);
		cmds->rd[cmds->cc][cmds->hdp] = -1;
		cmds->hdp = -1;
	}
	while (i < cmds->efdp)
	{
		if (cmds->fd[i] >= 0)
		{
			close(cmds->fd[i]);
			cmds->fd[i] = -1;
		}
		i++;
	}
	cmds->bfdp = cmds->efdp;
}

/**
 * @brief This function will simulate the heredoc redirection.
 * @param cmds This holds the commands struct.
 * @return 0 if failed
 * @return 1 if succeeded.
 */
int	process_heredoc(t_commands *cmds)
{
	int		fd;
	char	*tmp;

	if (cmds->hdp < 0)
		return (0);
	fd = open(TEMP_FILE, cmds->t, PERMS);
	if (fd < 0)
		return (perror("Failed to create temp file"), 0);
	tmp = readline("Martho Heredoc> ");
	while (tmp != NULL && !ft_strcmp(cmds->files[cmds->hdp], tmp))
	{
		if (tmp)
		{
			ft_putendl_fd(tmp, fd);
			free(tmp);
		}
		tmp = readline("Martho Heredoc> ");
	}
	if (tmp)
		free(tmp);
	return (close(fd), 1);
}

/**
 * @brief This function will check if the file is it's exsistance.
 * @param cmds This holds the command struct.
 * @return Whatever access() returns.
 */
int	check_file(t_commands *cmds)
{
	return (access(cmds->files[cmds->cf], F_OK));
}
