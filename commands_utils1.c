/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/10/11 15:49:47 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
	@brief				This function will execute the echo command and will p-
						-rint what the user has entered.
	@param	commands	This holds the user input.
	@param	len			This holds the length of the commands that was passed.
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

void	process_parent(char **bdir, char **commands, pid_t cpid, int *fd)
{
	int		i;
	char	**out;

	waitpid(cpid, NULL, 0);
	out = create_argv(fd[0]);
	if (!out)
		return ;
	i = 0;
	while (bdir[i] && ft_execute(bdir[i], commands))
		i++;
	free_split(out);
	close_pipes(fd);
}

void	process_child(char **bdir, char **commands, int *fd)
{
	printf("Processing child\n");
	int	i;

	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), exit(EXIT_FAILURE));
	i = 0;
	while (bdir[i] && ft_execute(bdir[i], commands))
		i++;
	exit(EXIT_SUCCESS);
}

/*
	@brief				This function will be executed only if the user has pa-
						-ssed one command e.g.: ls, touch, nano, etc...
	@param	commands	This holds the command we want to pass.
	@param	bdir		This holds the binary file path.
	@return				void (Nothing).
*/
void	one_command(char **commands, char **bdir)
{
	int		i;
	pid_t	childpid;

	childpid = fork();
	if (!childpid)
	{
		i = 0;
		while (bdir[i] && ft_execute(bdir[i], commands))
			i++;
		exit(EXIT_SUCCESS);
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
}

/*
	@brief				This function will process the passed executable name
						based on the enviorment vairable(PATH).
	@param	commands	This holds the commands that was passed.
	@param	av			This holds the stdout data. It can be NULL also.
	@var	bdir		This will hold the PATH executable paths
	@var	childpid	This will hold the process id of the child.
	@var	i			This will iterate over bdir.
*/
void	execute_binary(char ***commands, size_t size)
{
	int		fd[2];
	char	**bdir;
	pid_t	childpid;
	size_t	i;

	if (pipe(fd) == -1)
		return ;
	bdir = ft_split(getenv("PATH"), ':');
	if (!bdir)
		return (close_pipes(fd));
	i = 0;
	if (size == 1)
		return (one_command(commands[0], bdir), close_pipes(fd));
	while (i < size)
	{
		childpid = fork();
		if (!childpid)
			process_child(bdir, commands[i], fd);
		else if (childpid > 0)
			process_parent(bdir, commands[i], childpid, fd);
		else if (childpid < 0)
			perror("Fork failed.");
		i++;
	}
	return (free_split(bdir), print_stdout(fd[0]), close_pipes(fd));
}
