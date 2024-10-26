/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redierctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamalmar <hamalmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 22:06:08 by hamad             #+#    #+#             */
/*   Updated: 2024/10/26 13:40:59 by hamalmar         ###   ########.fr       */
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
void	redierct_to_file(char **bdir, char **commands, int troa)
{
	int		fd;
	int		childpid;
	char	**tmp;
	size_t	i;

	fd = open(commands[count_split(commands) - 1], O_WRONLY | O_CREAT | troa, 0664);
	if (fd < 0)
		return ;
	childpid = fork();
	if (!childpid)
	{
		tmp = NULL;
		i = 0;
		if (troa == O_TRUNC)
			tmp = trim_command(ft_subsplit(commands, REDICERTION_TO_FILE));
		else if (troa == O_APPEND)
			tmp = trim_command(ft_subsplit(commands, APPEND_REDIRECTION));
		if (!tmp || dup2(fd, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		while (bdir[i])
			ft_execute(bdir[i++], tmp);
		return (free_split(tmp), close(fd), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(fd);
}
/**
 * @brief	This function will redirect a file or some data to the input of th-
 * 			-e passed command.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
*/
void	redierct_to_input(char **bdir, char **commands)
{
	int		fd;
	int		childpid;
	char	**tmp;
	size_t	i;

	fd = open(commands[count_split(commands) - 1], O_RDONLY);
	if (fd < 0)
		return ;
	childpid = fork();
	if (!childpid)
	{
		tmp = trim_command(ft_subsplit(commands, REDIRECTION_TO_INPUT));
		if (!tmp || dup2(fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		i = 0;
		while (bdir[i])
			ft_execute(bdir[i++], tmp);
		return (free_split(tmp), close(fd), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(fd);
}
/**
 * @brief	This function will mimic the behavior of heredoc.
 * @param	bdir	This will hold the path of the executable.
 * @param	commands	This holds the command that was passed by the user.
 * @return	Void.
 */
void	heredoc_to_input(char **bdir, char **commands)
{
	char	*line;
	char	*delimeter;
	int		fd;

	delimeter = commands[count_split(commands) - 1];
	if (!delimeter || ft_strcmp(delimeter, HEREDOC_REDIRECTION))
		return (perror("Bad delimeter"));
	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	line = readline("> ");
	while (1 && fd > 0 && !ft_strcmp(line, delimeter))
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
	if (delimeter && !delimeter[0])
		free(delimeter);
	close(fd);
	normal_process(bdir, commands, TEMP_FILE, HEREDOC_REDIRECTION);
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
void	normal_process(char **bdir, char **commands, char *fname, char *dlmtr)
{
	int		childpid;
	char	**tmp;
	size_t	i;
	int		fd;

	childpid = fork();
	if (!childpid)
	{
		i = 0;
		if (fname && fname[0] && dlmtr)
		{
			tmp = trim_command(ft_subsplit(commands, dlmtr));
			fd = open(fname, O_RDONLY);
			if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
				return (perror("bad file descriptor"), exit(EXIT_FAILURE));
			close(fd);
		}
		else
			tmp = trim_command(commands);
		while (tmp && tmp[0] && bdir[i])
			ft_execute(bdir[i++], tmp);
		return (free_split(tmp), exit(EXIT_SUCCESS));
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
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
