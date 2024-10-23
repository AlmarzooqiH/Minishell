/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redierctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/10/23 21:15:07 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	redierct_to_file(char **bdir, char **commands)
{
	int		fd;
	int		childpid;
	char	**tmp;
	size_t	i;

	fd = open(commands[count_split(commands) - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
		return ;
	childpid = fork();
	if (!childpid)
	{
		dup2(fd, STDOUT_FILENO);
		i = 0;
		tmp = ft_subsplit(commands, REDICERTION_TO_FILE);
		if (!tmp)
			exit(EXIT_FAILURE);
		while (bdir[i])
			ft_execute(bdir[i++], tmp);
		free_split(tmp);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(fd);
}

void	redierct_to_input(char **bdir, char **commands, int fd[][2], size_t cpipe)
{
	(void)bdir;	
	(void)commands;	
	(void)fd;	
	(void)cpipe;	
}

void	append_to_file(char **bdir, char **commands)
{
	int		fd;
	int		childpid;
	char	**tmp;
	size_t	i;

	fd = open(commands[count_split(commands) - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd < 0)
		return ;
	childpid = fork();
	if (!childpid)
	{
		dup2(fd, STDOUT_FILENO);
		i = 0;
		tmp = ft_subsplit(commands, APPEND_REDIRECTION);
		if (!tmp)
			exit(EXIT_FAILURE);
		while (bdir[i])
			ft_execute(bdir[i++], tmp);
		free_split(tmp);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(fd);	
}

void	herdoc_to_input(char **bdir, char **commands, int fd[][2], size_t cpipe)
{	
		(void)bdir;	
	(void)commands;	
	(void)fd;	
	(void)cpipe;	
}

/**
 * @brief	This function will check if the passed command contained any redir-
 * 			-ection operators('>', '<', '>>', '<<').
 * @param	commad		This will hold the passed in command.
 * @param	split_size	This holds the size of the command.
 * @return	-1 if there is no redirections
 * @return	e_redirection_to_file if the command had '>'.
 * @return	e_redirection_to_input if the command had '<'.
 * @return	e_append_redirection if the command had '>>'.
 * @return	e_heredoc_redirection if the command had '<<'.
*/
int	is_redirection(char **command, size_t split_size)
{
	size_t	i;

	i = 0;
	while (i < split_size)
	{
		if (ft_strcmp(command[i], REDICERTION_TO_FILE))
			return (e_redirection_to_file);
		else if (ft_strcmp(command[i], REDIRECTION_TO_INPUT))
			return (e_redirection_to_input);
		else if (ft_strcmp(command[i], APPEND_REDIRECTION))
			return (e_append_redirection);
		else if (ft_strcmp(command[i], HEREDOC_REDIRECTION))
			return (e_heredoc_redirection);
		i++;
	}
	return (-1);
}
