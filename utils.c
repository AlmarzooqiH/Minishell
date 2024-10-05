/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:26:39 by hamad             #+#    #+#             */
/*   Updated: 2024/10/05 20:42:44 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
	@brief				This function will check if the passed commands contain
						 a pipe('|').
	@param	commands	This will hold all of the commands passed by the shell.
	@param	len			This holds the length of the commands.
*/
int	has_pipe(char **commands, size_t len)
{
	size_t	i;

	if (!commands || !(*commands))
		return (0);
	while (i < len)
	{
		if (ft_strcmp(commands[i], PIPE))
			return (1);
		i++;
	}
	return (0);
}

/*
	@brief			This function will check if the desired flag is present in
					command that we want to check.
	@param	flag	The flag that we want to check in the passed command.
	@param	flag_in	The flag that we got from the user input.
*/
int	has_flag(char *flag, char *flag_in)
{
	return (ft_strcmp(flag_in, flag));
}

/*
	@brief				This will execute the passed executable.
	@param	pvar		This holds the path variable(PATH, HOME, USER, etc...).
	@param	commands	This holds the commands that was passed.
	@var	temp		This will hold the path of the PATH enviorment variable
	@var	bpath		This will hold the exectuable/binary file path which is
						temp/binary or temp/exectuable.
*/
void	ft_execute(char	*pvar, char **commands)
{
	char	*temp;
	char	*bpath;

	temp = ft_strjoin(pvar, "/");
	if (!temp)
		return ;
	bpath = ft_strjoin(temp, commands[0]);
	if (!bpath)
		return ;
	execve(bpath, commands, NULL);
	free(temp);
	free(bpath);
}

/*
	@brief This function will print the content of stdout.
	@var	s	Will hold each line of the stdout.
	@var	fd	The file descriptor.
*/
void	print_stdout(void)
{
	char	*s;
	int		fd;

	fd = open("out.txt", O_RDONLY);
	if (fd < 0)
		return ;
	s = get_next_line(fd);
	while (s)
	{
		printf("%s", s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}
