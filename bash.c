/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:31:03 by hamad             #+#    #+#             */
/*   Updated: 2024/12/31 14:07:23 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This command will check if the command in in bash syntax or not e.g.:
 * <filein command or <<delimeter command.
 * @param	command	This holds the command we want to check.
 * @return 1 if the command is in bash syntax, 0 otherwise.
 */
int	is_bashsyntax(char **command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command[0], APPEND_REDIRECTION)
		|| ft_isprefix(command[0], APPEND_REDIRECTION))
		return (1);
	else if (ft_strcmp(command[0], HEREDOC_REDIRECTION)
		|| ft_isprefix(command[0], HEREDOC_REDIRECTION))
		return (1);
	else if (ft_strcmp(command[0], REDICERTION_TO_FILE)
		|| ft_isprefix(command[0], REDICERTION_TO_FILE))
		return (1);
	else if (ft_strcmp(command[0], REDIRECTION_TO_INPUT)
		|| ft_isprefix(command[0], REDIRECTION_TO_INPUT))
		return (1);
	return (0);
}

/**
 * @brief This function will check if the current input is a redirection but a-
 * -lone like this: cat < filein or < file in cat -e
 * @param	s	This holds the current string we want to check.
 * @return	1 if the input is a redirection alone, 0 otherwise.
 */
int	is_alone(char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, REDICERTION_TO_FILE))
		return (1);
	if (ft_strcmp(s, REDIRECTION_TO_INPUT))
		return (1);
	if (ft_strcmp(s, APPEND_REDIRECTION))
		return (1);
	if (ft_strcmp(s, HEREDOC_REDIRECTION))
		return (1);
	return (0);
}

/**
 * @brief This function will execute the command that is in bash syntax.
 * @param	cmds	This holds the commands struct.
 * @return Void.
 */
void	execute_bash(t_commands *cmds)
{
	pid_t	cid;
	int		i;
	char	**scmd;

	cid = fork();
	if (!cid)
	{
		i = 0;
		scmd = extract_command(cmds);
		if (!scmd)
			return (perror("Failed to extract the command"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
		waitpid(cid, NULL, 0);
	}
}
