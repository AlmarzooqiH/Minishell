/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/11/24 02:08:55 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will extract the command from the tokenized commands.
 * @param cmds  This holds the commands struct.
 * @return  The extracted command.
 */
char    **extract_command(t_commands *cmds)
{
    size_t  i;
    size_t  j;
    char **cmd;

    if (cmds->is_bash[cmds->ccmd] && is_alone(cmds->cmds[cmds->ccmd][0]))
        i = 2;
    else if (cmds->is_bash[cmds->ccmd] && !is_alone(cmds->cmds[cmds->ccmd][0]))
        i = 1;
    else
        i = 0;
    j = i;
    while (cmds->cmds[cmds->ccmd][i] && !(is_redirection(cmds->cmds[cmds->ccmd][i]) >= 0))
        i++;
    cmd = trim_command(ft_subnsplit(cmds->cmds[cmds->ccmd], j, i));
    return (cmd);
    
}
void    execute_one(t_commands *cmds)
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
			return (perror("Failed to extract the command"), exit(EXIT_FAILURE));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else
        waitpid(cid, NULL, 0);
}

void    execute_cmd(t_commands *cmds)
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
			return (perror("Failed to extract the command"), exit(EXIT_FAILURE));
        if (dup_pipes(cmds->fd, cmds->cpipe, 2) == -1)
            return (perror("Failed to dup pipes"), exit(EXIT_FAILURE));
        close_pipe(cmds->fd[cmds->cpipe], 1);
        close_pipe(cmds->fd[cmds->cpipe + 1], 0);
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else
	{
        close_pipe(cmds->fd[cmds->cpipe], 2);
        close_pipe(cmds->fd[cmds->cpipe + 1], 1);
        waitpid(cid, NULL, 0);
    }
}

void    execute_last(t_commands *cmds)
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
			return (perror("Failed to extract the command"), exit(EXIT_FAILURE));
        if (dup_pipes(cmds->fd, cmds->cpipe - 1, 0) == -1)
            return (perror("Failed to dup pipes"), exit(EXIT_FAILURE));
        close_pipe(cmds->fd[cmds->cpipe], 1);
        close_pipe(cmds->fd[cmds->cpipe + 1], 0);
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else
	{
        close_pipe(cmds->fd[cmds->cpipe], 2);
		close_pipe(cmds->fd[cmds->cpipe + 1], 1);
        waitpid(cid, NULL, 0);
    }
}

void    execute_binary(t_commands *cmds)
{
    if (cmds->nscmds == 1)
        return (execute_one(cmds));
    while (cmds->ccmd < cmds->nscmds - 1)
    {
        execute_cmd(cmds);
        cmds->ccmd++;
		cmds->cpipe++;
    }
    execute_last(cmds);
}
