/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:05:16 by hamad             #+#    #+#             */
/*   Updated: 2024/11/18 21:04:37 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief	This function will count the number of redirections that are prese-
 * 			-nt within the command.
 * @param	command This holds the command that was passed.
 * @return	Will return the number of redirections within the command.
 */
size_t	count_redirections(char **command)
{
	size_t	n;
	size_t	i;

	if (!command)
		return (0);
	i = 0;
	n = 0;
	while (command[i] != NULL)
	{
		if (ft_strcmp(command[i], APPEND_REDIRECTION) || ft_isprefix(command[i], APPEND_REDIRECTION))
			n++;
		else if (ft_strcmp(command[i], HEREDOC_REDIRECTION) || ft_isprefix(command[i], HEREDOC_REDIRECTION))
			n++;
		else if (ft_strcmp(command[i], REDICERTION_TO_FILE) || ft_isprefix(command[i], REDICERTION_TO_FILE))
			n++;
		else if (ft_strcmp(command[i], REDIRECTION_TO_INPUT) || ft_isprefix(command[i], REDIRECTION_TO_INPUT))
			n++;
		i++;
	}
	return (n);
}
/**
 * @brief	This function will process any rediection based on the user input.
 * @param	bdir	Binary/executable path.
 * @param	command	This will hold in the current command.
 * @param	fname	This will hold the filename(Can be NULL).
 * @param	re		This holds the type of redierction we got. If -1 this mean-
 * -s there are no redierections and will be processed normally.
 * @param	cflag	This will hold the 1 if there is a command and 0 if there
 * are no commands.
 * @return Void.
*/
// void	process_redirection(char **bdir, char **command, char *fname, int re, int *cflag, int (*fd)[2], size_t *cpipe)
// {
// 	if (!command || !command[0])
// 		return (perror("Command is empty."));
// 	if (*cflag)
// 	{
// 		*cflag = 0;
// 		if (re == e_redirection_to_file)
// 			return (redierct_to_file(bdir, command, fname, fd, cpipe, O_TRUNC));
// 		else if (re == e_redirection_to_input)
// 			return (redierct_to_input(bdir, command, fname, fd, cpipe));
// 		else if (re == e_append_redirection)
// 			return (redierct_to_file(bdir, command, fname, fd, cpipe, O_APPEND));
// 		else if (re == e_heredoc_redirection)
// 			return (heredoc_to_input(bdir, command, fname, fd, cpipe));
// 		else
// 			return (normal_process(bdir, command, NULL, NULL, NULL));
// 	}
// 	redierct_to_files(fname, re, fd, cpipe);
// }
/**
 * @brief This function will count how many redierctions we got inside the com-
 * -mands.
 * @param	commands	This holds the commands that was passed.
 * @return	Will return the total number of redierctions.
*/
size_t	get_total_rediractions(char ***commands)
{
	size_t	i;
	size_t	total;

	if (!commands || !commands[0])
		return (0);
	i = 0;
	total = 0;
	while (commands[i] != NULL)
		total += count_redirections(commands[i++]);
	return (total);
}

// void	redierct_to_files(char *fname, int re, int (*fd)[2], size_t *cpipe)
// {
// 	int		file;
// 	char	*line;

// 	if (!fname)
// 		return (perror("Failed to get filename."));
// 	file = 0;
// 	if (re == e_redirection_to_file)
// 		file = open(fname, O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSIONS);
// 	else if (re == e_append_redirection)
// 		file = open(fname, O_WRONLY | O_CREAT | O_APPEND, FILE_PERMISSIONS);
// 	if (file < 0)
// 		return (perror("Failed to open file."));
// 	line = get_next_line(fd[*cpipe][0]);
// 	while (line && line[0] != '\0')
// 	{
// 		write(file, line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(fd[*cpipe][0]);
// 	}
// 	if (line)
// 		free(line);
// 	close(file);
// 	close_pipe(fd[*cpipe], 2);
// }
