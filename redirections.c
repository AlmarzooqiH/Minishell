/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/11/08 00:50:00 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will redierct the output of the command that was pas-
 * -sed to a file.
 * @param	bdir	This holds the executable path.
 * @param	commands	This holds the command that was passed in.
 * @param	troa		Truncate or append.
 * @return	void
 */
void	redierct_to_file(char **bdir, char **commands, char *file_name, int troa, int (*rfd)[2], int cpipe)
{
	int		fd;
	int		childpid;
	size_t	i;

	if (!file_name)
		return (perror("Please provide a file name"));
	fd = open(file_name, O_WRONLY | O_CREAT | troa, FILE_PERMISSIONS);
	if (fd < 0)
		return (perror("Bad file descriptor"));
	childpid = fork();
	if (!childpid)
	{
		i = 0;
		if (dup2(fd, STDOUT_FILENO) == -1 || dup_pipes(rfd, cpipe, 2) == -1)
			exit(EXIT_FAILURE);
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (close(fd), close_pipe(rfd[cpipe + 1], 0), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	return(close(fd), close_pipe(rfd[cpipe + 1], 1));
}

/**
 * @brief	This function will redirect a file or some data to the input of th-
 * 			-e passed command.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
 */
void	redierct_to_input(char **bdir, char **commands, char *fname, int (*rfd)[2], int cpipe)
{
	int		fd;
	int		childpid;
	size_t	i;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (perror("Bad file descriptor"));
	childpid = fork();
	if (!childpid)
	{
		if (dup2(fd, STDIN_FILENO) == -1 || dup_pipes(rfd, cpipe, 2) == -1)
			return (perror("Dup failed"), exit(EXIT_FAILURE));
		i = 0;
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (close(fd), close_pipe(rfd[cpipe + 1], 0), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	return(close(fd), close_pipe(rfd[cpipe + 1], 1));
}

/**
 * @brief	This function will mimic the behavior of heredoc.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
 */
void	heredoc_to_input(char **bdir, char **commands, char *dlmtr, int (*rfd)[2], int cpipe)
{
	char	*line;
	int		fd;

	if (!dlmtr || ft_strcmp(dlmtr, HEREDOC_REDIRECTION))
		return (perror("Bad delimeter"));
	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	line = readline("> ");
	while (1 && fd > 0 && !ft_strcmp(line, dlmtr))
	{
		if (line)
		{
			ft_putendl_fd(line, fd);
			free(line);
		}
		line = readline("> ");
	}
	if (line && !line[0])
		free(line);
	close(fd);
	normal_process(bdir, commands, TEMP_FILE, rfd, cpipe);
	unlink(TEMP_FILE);
}

/**
 * @brief	This function will process a normal command passed by the user.
 * @param	bdir		This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @param	fname		This will hold a filename. (Can be NULL)
 * @param	dlmtr		This will hold a seperator in the command. (Can be-
 * 						- NULL).
 * @return				Void.
 */
void	normal_process(char **bdir, char **commands, char *fname, int (*rfd)[2], int cpipe)
{
	int		childpid;
	size_t	i;
	int		fd;

	childpid = fork();
	if (!childpid)
	{
		i = 0;
		if (fname && fname[0])
		{
			fd = open(fname, O_RDONLY);
			if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
				return (perror("Bad file descriptor"), exit(EXIT_FAILURE));
			close(fd);
		}
		if (rfd && dup_pipes(rfd, cpipe, 2) == -1)
			return (perror("Failed to dup rpipe pipes"), exit(EXIT_FAILURE));
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (close_pipe(rfd[cpipe + 1], 0), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	return(close_pipe(rfd[cpipe + 1], 1));
}

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
	if (ft_strcmp(command, REDICERTION_TO_FILE) || ft_isprefix(command, REDICERTION_TO_FILE))
		return (e_redirection_to_file);
	else if (ft_strcmp(command, REDIRECTION_TO_INPUT) || ft_isprefix(command, REDIRECTION_TO_INPUT))
		return (e_redirection_to_input);
	else if (ft_strcmp(command, APPEND_REDIRECTION) || ft_isprefix(command, APPEND_REDIRECTION))
		return (e_append_redirection);
	else if (ft_strcmp(command, HEREDOC_REDIRECTION) || ft_isprefix(command, HEREDOC_REDIRECTION))
		return (e_heredoc_redirection);
	return (-1);
}
