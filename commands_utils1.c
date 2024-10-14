/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/10/14 21:30:26 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
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

/*
	@brief				This function will be executed only if the user has pa-
						-ssed one command e.g.: ls, touch, nano, etc...
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@return				void (Nothing).
*/
void	one_command(char **bdir, char **commands, int *fd)
{
	int		i;
	pid_t	childpid;
	childpid = fork();
	if (!childpid)
	{
		if (fd)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				perror("stdout dup2 failed");
			close_pipes(fd);
		}
		i = 0;
		while (bdir[i] && ft_execute(bdir[i], commands))
			i++;
		exit(EXIT_SUCCESS);
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
}

/*
	@brief				This function will process the secondary command and w-
						-ill redirect the prevoius output to this current one.
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@param	cpid		Child process id.
	@param	fd			This will hold the pipeline file descriptors.
	@return				void (Nothing).
*/
void	process_parent(char **bdir, char **commands, int *fd)
{
	int		i;
	pid_t	ppid;
	char	**new_commands;

	i = 0;
	ppid = fork();
	if (!ppid)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close_pipes(fd);
		new_commands = trim_command(commands);
		if (!new_commands)
			exit(EXIT_FAILURE);
		while (bdir[i] && ft_execute(bdir[i],  new_commands))
			i++;
		free_split(new_commands);
		exit(EXIT_SUCCESS);
	}
	if (ppid > 0)
	{
		close_pipes(fd);
		waitpid(ppid, NULL, 0);
	}
}

/*
	@brief				This function will process the passed executable name
						based on the enviorment vairable(PATH).
	@param	commands	This holds the commands that was passed.
	@param	av			This holds the stdout data. It can be NULL also.
	@var	bdir		This will hold the PATH executable paths
	@var	childpid	This will hold the process id of the child.
	@var	i			This will iterate over the commands param.
	@return				void (Nothing).
*/
//Figure out how to pipe two processes then proceed with the multiple pipes.
void	execute_binary(char ***commands, size_t size)
{
	int		fd[2]; 
	char	**bdir;
	// size_t	i;

	bdir = ft_split(getenv("PATH"), ':');
	if (!bdir)
		return ;
	if (size == 1)
		return (one_command(bdir, commands[0], NULL), free_split(bdir));
	if (pipe(fd) == -1)
		return (free_split(bdir));
	one_command(bdir, commands[0], fd);
	process_parent(bdir, commands[1], fd);
	return (free_split(bdir));
}
