/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/10/02 19:54:16 by hamad            ###   ########.fr       */
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

/*
	@brief				This function will process the passed executable name
						based on the enviorment vairable(PATH).
	@param	commands	This holds the commands that was passed.
	@var	bdir		This will hold the PATH executable paths
	@var	childpid	This will hold the process id of the child.
	@var	i			This will iterate over bdir.
*/
void	execute_binary(char	**commands)
{
	char	**bdir;
	pid_t	childpid;
	size_t	i;
	int		fd;

	childpid = fork();
	if (!childpid)
	{
		bdir = ft_split(getenv("PATH"), ':');
		if (!bdir)
			exit(EXIT_FAILURE);
		i = 0;
		while (bdir[i])
			ft_execute(bdir[i++], commands);
		free_split(bdir);
		close(fd);
		return ;
	}
	else if (childpid > 0)
		waitpid(childpid, NULL, 0);
	close(fd);
}
