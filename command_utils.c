/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/11/06 08:58:00 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
	@brief				This function will execute the echo command and will p-
						-rint what the user has entered.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
	@return				void (Nothing).
*/
void	process_echo(char **commands, size_t len)
{
	size_t	i;
	size_t	j;

	if (has_flag(NL_FLAG, commands[1]))
		i = 2;
	else
		i = 1;
	while (i < len)
	{
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '\'' || commands[i][j] == '\"')
			{
				j++;
				continue ;
			}
			write(STDOUT_FILENO, &commands[i][j], 1);
			j++;
		}
		if (i++ != len - 1)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!has_flag(NL_FLAG, commands[1]))
		write(1, "\n", 1);
}

/**
	@brief				This function will be executed only if the user has pa-
						-ssed one command e.g.: ls, touch, nano, etc...
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@param	cpipe		This holds the value of the current pipe. (0 - npipes).
	@return				void (Nothing).
*/
void	one_command(char **bdir, char **commands, int (*fd)[2], size_t cpipe)
{
	int		redirection;
	size_t	n_redirections;

	(void)fd;
	(void)cpipe;
	(void)n_redirections;
	if (!commands)
		return ;
	n_redirections = count_redirections(commands);
	redirection = is_redirection(commands[0]);
	if (redirection == e_redirection_to_file)
		return (redierct_to_file(bdir, commands, NULL, O_TRUNC));
	else if (redirection == e_redirection_to_input)
		return (redierct_to_input(bdir, commands, NULL));
	else if (redirection == e_append_redirection)
		return (redierct_to_file(bdir, commands, NULL, O_APPEND));
	else if (redirection == e_heredoc_redirection)
		return (heredoc_to_input(bdir, commands, NULL));
	else
		return (normal_process(bdir, commands, NULL));
}

/**
	@brief				This function will process the secondary command and w-
						-ill redirect the prevoius output to this current one.
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@param	cpid		Child process id.
	@param	fd			This will hold the pipeline file descriptors.
	@param	cpipe		This holds the value of the current pipe. (0 - npipes).
	@return				void (Nothing).
*/
void	process_parent(char **bdir, char **commands, int (*fd)[2], size_t cpipe)
{
	int		i;
	pid_t	ppid;
	char	**new_commands;

	if (!commands)
		return ;
	i = 0;
	ppid = fork();
	if (!ppid)
	{
		dup_pipes(fd, cpipe, 2);
		close_pipe(fd[cpipe + 1], 0);
		new_commands = trim_command(commands);
		if (!new_commands)
			exit(EXIT_FAILURE);
		while (bdir[i] && ft_execute(bdir[i], new_commands))
			i++;
		return (free_split(new_commands), exit(EXIT_SUCCESS));
	}
	if (ppid > 0)
	{
		close_pipe(fd[cpipe], 2);
		close_pipe(fd[cpipe + 1], 1);
		waitpid(ppid, NULL, 0);
	}
}

/**
	@brief				This function will process the N-th command.
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@param	cpid		Child process id.
	@param	fd			This will hold the pipeline file descriptors.
	@param	cpipe		This holds the value of the current pipe. (0 - npipes).
	@return				void (Nothing).
*/
void	last_command(char **bdir, char **commands, int (*fd)[2], size_t cpipe)
{
	int		i;
	pid_t	ppid;
	char	**new_commands;

	if (!commands)
		return ;
	i = 0;
	ppid = fork();
	if (!ppid)
	{
		dup_pipes(fd, cpipe, 0);
		close_pipe(fd[cpipe], 1);
		new_commands = trim_command(commands);
		if (!new_commands)
			exit(EXIT_FAILURE);
		while (bdir[i] && ft_execute(bdir[i], new_commands))
			i++;
		return (free_split(new_commands), exit(EXIT_SUCCESS));
	}
	if (ppid > 0)
	{
		close_pipe(fd[cpipe], 2);
		waitpid(ppid, NULL, 0);
	}
}

/**
*	@brief				This function will process the passed executable name
						based on the enviorment vairable(PATH).
*	@param	commands	This holds the commands that was passed.
*	@param	size		This holds the size of the commands.
*	@var	bdir		This will hold the PATH executable paths
*	@var	i			This will iterate over the commands param.
*	@return				void (Nothing).
*/
void	execute_binary(char ***commands, size_t size)
{
	char	**bdir;
	size_t	i;
	int		(*fd)[2];

	fd = NULL;
	bdir = ft_split(getenv("PATH"), ':');
	if (!bdir)
		return ;
	// if (size == 1)
	// 	return (one_command(bdir, commands[0], NULL, 0), free_split(bdir));
	if (init_pipes(&fd, size - 1) == -1)
		return (free_split(bdir), perror("Failed to init pipes"));
	i = 0;
	while (i < size)
	{
		if (is_bashsyntax(commands[i]))
			process_bash(bdir, commands[i], fd[i]);
		else
			one_command(bdir, commands[i], fd, i);
		i++;
	}
	//Add this to the return statement when done: close_pipes(fd, size)
	return (close_pipes(fd, size - 1), free_split(bdir));
}
