/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:26:39 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 19:44:38 by hamad            ###   ########.fr       */
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
	size_t	i;
	int		n_pipes;

	if (!commands || !(*commands))
		return (0);
	i = 0;
	n_pipes = 1;
	while (i < ft_strlen(commands) && commands[i] != '\0')
	{
		if (is_quote(commands[i]))
		{
			i++;
			while (commands[i] && !is_quote(commands[i]))
				i++;
			if (commands[i])
				i++;
		}
		if (ft_contains(commands, '|') && commands[i] == '|')
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

/**
 * @brief This function will process the command that was passed in where the
 * command that was passed in had the entire path of the executable e.g:/bin/ls
 * @param	commands	This holds the command that was passed.
 * @return	0 if successful. 1 if failure.
 * @note	Might rewrite it later. It is too messy rn.
 */
int	ft_execute2(char **commands, char **envp)
{
	char	*b;
	char	**t;
	char	**y;
	char	**u;
	char	**s;

	b = ft_strdup(commands[0]);
	if (!b)
		return (1);
	t = ft_split(b, '/');
	if (!t)
		return (free(b), 1);
	y = ft_subnsplit(t, count_split(t) - 1, count_split(t));
	if (!y)
		return (free_variables(t, NULL, NULL, NULL), free(b), 1);
	u = ft_subnsplit(commands, 1, count_split(commands));
	if (!u)
		return (free_variables(t, y, NULL, NULL), free(b), 1);
	s = ft_join_split(y, u);
	if (!s)
		return (free_variables(t, y, u, NULL), free(b), 1);
	if (!access(b, X_OK) && execve(b, s, envp) == -1)
		return (perror("execve failed"), free(b), 1);
	return (free_variables(t, y, y, s), free(b), 0);
}

/*
	@brief This will execute the passed executable.
	@param	pvar This holds the path variable(PATH, HOME, USER, etc...).
	@param	commands This holds the commands that was passed.
	@var	temp This will hold the path of the PATH enviorment variable
	@var	bpath This will hold the exectuable/binary file path which is
						temp/binary or temp/exectuable.
	@return				0 if successful. 1 if failure.
*/
int	ft_execute(char	*pvar, char **commands, char **envp)
{
	char	*temp;
	char	*bpath;

	if (!ft_contains(commands[0], '/'))
	{
		temp = ft_strjoin(pvar, "/");
		if (!temp)
			return (perror("Failed to join"), 1);
		bpath = ft_strjoin(temp, commands[0]);
		if (!bpath)
			return (perror("Failed to join"), free(temp), 1);
		if (access(bpath, X_OK) == -1)
			return (free(temp), free(bpath), 1);
		if (execve(bpath, commands, envp) == -1)
			return (perror("execve failed"), free(temp), free(bpath), 1);
		return (free(temp), free(bpath), 0);
	}
	return (ft_execute2(commands, envp));
}

/**
 * @brief	This function will count the number of tokens inside the command.
 * @param	tokens	The tokens that we want to count.
 * @return	The number of tokens.
 */
int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
