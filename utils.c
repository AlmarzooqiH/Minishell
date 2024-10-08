/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:26:39 by hamad             #+#    #+#             */
/*   Updated: 2024/10/07 21:14:23 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
	@brief				This function will check if the passed commands contain
						 a pipe('|').
	@param	commands	This will hold all of the commands passed by the shell.
	@param	len			This holds the length of the commands.
	@return				The number of pipes found.
*/
int	has_pipe(char *commands)
{
	int	i;
	int	n_pipes;

	if (!commands || !(*commands))
		return (0);
	i = 0;
	n_pipes = 0;
	while (commands[i])
	{
		if (commands[i] == '|')
			n_pipes++;
		i++;
	}
	return (n_pipes);
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
	@param	av			This holds the stdout data. It can be NULL also.
	@var	temp		This will hold the path of the PATH enviorment variable
	@var	bpath		This will hold the exectuable/binary file path which is
						temp/binary or temp/exectuable.
	@return				Nothing.
*/
int	ft_execute(char	*pvar, char **commands, char **av)
{
	char	*temp;
	char	*bpath;
	int		exit_status;

	temp = ft_strjoin(pvar, "/");
	if (!temp)
		return (EXIT_FAILURE);
	if (av)
		bpath = ft_strjoin(temp, av[0]);
	else
		bpath = ft_strjoin(temp, commands[0]);
	if (!bpath)
		return (EXIT_FAILURE);
	if (av)
		exit_status = execve(bpath, av, NULL);
	else
		exit_status = execve(bpath, commands, NULL);
	free(temp);
	free(bpath);
	if (exit_status == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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

/*
	@brief	This function will read the stdout file and create argv to redirect
			to the next command.
	@return	This will return a char ** That contains the stdout.
*/
char	**create_argv(void)
{
	char		**av;
	char		*temp;
	int			fd;
	long		n_lines;
	long		i;

	fd = open("out.txt", O_RDONLY);
	n_lines = count_lines();
	if (fd < 0 || n_lines <= 0)
		return (close(fd), NULL);
	av = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (!av)
		return (NULL);
	i = 0;
	while (i < n_lines)
	{
		temp = get_next_line(fd);
		if (!temp)
			return (free(temp), NULL);
		av[i] = ft_strtrim(temp, "\n");
		if (!av[i++])
			return (free_split(av), NULL);
	}
	av[i] = NULL;
	return (close(fd), av);
}
