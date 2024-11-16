/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/11/14 21:01:13 by hamad            ###   ########.fr       */
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
void	redierct_to_file(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe, int troa)
{
	int		file;
	int		childpid;
	size_t	i;

	(void)cpipe, (void)fd;
	if (!fname)
		return (perror("Please provide a file name"));
	file = open(fname, O_WRONLY | O_CREAT | troa, FILE_PERMISSIONS);
	if (file < 0)
		return (perror("Bad file descriptor"));
	childpid = fork();
	if (!childpid)
	{
		i = 0;
		if (dup2(file, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (close(file), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(file);
}

/**
 * @brief	This function will redirect a file or some data to the input of th-
 * 			-e passed command.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
 */
void	redierct_to_input(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe)
{
	int		file;
	int		childpid;
	size_t	i;

	file = open(fname, O_RDONLY);
	if (file < 0)
		return (perror("Bad file descriptor"));
	childpid = fork();
	if (!childpid)
	{
		if (dup2(file, STDIN_FILENO) == -1 || (fd && dup_pipes(fd, *cpipe, 1) == -1))
			return (perror("Dup failed"), close_pipe(fd[*cpipe], 0), exit(EXIT_FAILURE));
		i = 0;
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (close(file), close_pipe(fd[*cpipe], 0), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(file);
	close_pipe(fd[*cpipe], 1);
}

/**
 * @brief	This function will mimic the behavior of heredoc.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
 */
void	heredoc_to_input(char **bdir, char **commands, char *dlmtr, int (*fd)[2], size_t *cpipe)
{
	char	*line;
	int		file;

	if (!dlmtr || ft_strcmp(dlmtr, HEREDOC_REDIRECTION))
		return (perror("Bad delimeter"));
	file = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS);
	line = readline("> ");
	while (1 && file > 0 && !ft_strcmp(line, dlmtr))
	{
		if (line)
		{
			ft_putendl_fd(line, file);
			free(line);
		}
		line = readline("> ");
	}
	if (line)
		free(line);
	close(file);
	normal_process(bdir, commands, TEMP_FILE, fd, cpipe);
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
void	normal_process(char **bdir, char **commands, char *fname, int (*fd)[2], size_t *cpipe)
{
	int		childpid;
	size_t	i;
	int		file;

	childpid = fork();
	if (!childpid)
	{
		i = 0;
		if (fname && fname[0])
		{
			file = open(fname, O_RDONLY);
			if (file < 0 || dup2(file, STDIN_FILENO) == -1)
				return (perror("Bad file descriptor"), exit(EXIT_FAILURE));
			close(file);
		}
		if (fd && dup_pipes(fd, *cpipe, 1) == -1)
			return (perror("Failed to dup or close"), exit(EXIT_FAILURE));
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		return (exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	if (fd && fd[*cpipe][1] >= 0)
		close_pipe(fd[*cpipe], 1);
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
	if (ft_strcmp(command, APPEND_REDIRECTION) || ft_isprefix(command, APPEND_REDIRECTION))
		return (e_append_redirection);
	else if (ft_strcmp(command, HEREDOC_REDIRECTION) || ft_isprefix(command, HEREDOC_REDIRECTION))
		return (e_heredoc_redirection);
	else if (ft_strcmp(command, REDICERTION_TO_FILE) || ft_isprefix(command, REDICERTION_TO_FILE))
		return (e_redirection_to_file);
	else if (ft_strcmp(command, REDIRECTION_TO_INPUT) || ft_isprefix(command, REDIRECTION_TO_INPUT))
		return (e_redirection_to_input);
	return (-1);
}
