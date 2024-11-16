/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/11/16 13:31:51 by hamad            ###   ########.fr       */
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
void	one_command(char **bdir, char **commands, int (*fd)[2], size_t *cpipe)
{
	size_t	i;
	int		re;
	char	**sub_command;

	if (!commands || !commands[0])
		return (perror(""));
	if (is_bashsyntax(commands))
	{
		re = is_redirection(commands[0]);
		process_bash(bdir, commands, fd, cpipe, 1);
		if (re == e_redirection_to_input || re == e_heredoc_redirection)
			print_stdout(fd[*cpipe][0]);
		return ;
	}
	i = 0;
	while (commands[i] != NULL && !(is_redirection(commands[i]) >= 0))
		i++;
	sub_command = trim_command(ft_subnsplit(commands, 0, i));
	if (!sub_command)
		return (perror("Failed to get the subcommand"));
	//Add getting the files and redirecting the output to it.
	normal_process(bdir, sub_command, NULL, fd, cpipe);
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
		return (free_split(1, new_commands), exit(EXIT_SUCCESS));
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
		return (free_split(1, new_commands), exit(EXIT_SUCCESS));
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
	size_t	cpipe;

	fd = NULL;
	bdir = ft_split(getenv("PATH"), ':');
	if (!bdir)
		return (perror("Failed to get the PATH variable."));
	if (init_pipes(&fd, size, get_total_rediractions(commands)) == -1)
		return (free_split(1, bdir), perror("Failed to init pipes"));
	cpipe = 0;
	if (size == 1 && get_total_rediractions(commands) == 1)
		return (one_command(bdir, commands[0], fd, &cpipe), free(bdir), close_pipes(fd, size));
	i = 0;
	while (i < size)
	{
		if (is_bashsyntax(commands[i]))
			process_bash(bdir, commands[i], fd, &cpipe, ((size - 1) + (get_total_rediractions(commands) - 1)));
		else
			normal_process(bdir, commands[i], NULL, fd, &cpipe);
		i++;
	}
	return (close_pipes(fd, ((size - 1) + (get_total_rediractions(commands)))), free_split(1, bdir));
}
