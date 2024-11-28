/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/11/28 19:22:09 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	execute_one_pipe(t_commands *cmds)
{
	pid_t	cid;
	int		i;
	char	**scmd;

	cid = fork();
	if (!cid)
	{
		scmd = extract_command(cmds);
		if (!scmd)
			return (perror("Failed to extract the command"), exit(EF));
		i = 0;
		dup_pipes(cmds);
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
		if (cmds->ccmd == 0)
			close(cmds->fd[cmds->cpipe][1]);
		else if (cmds->ccmd == 1)
			close(cmds->fd[cmds->cpipe][0]);
		waitpid(cid, NULL, 0);
	}
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
			return (perror("Failed to extract the command"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
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
        if (dup_pipes(cmds) == -1)
            return (perror("Failed to dup pipes"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
		if (cmds->cpipe > 0)
        	close_pipe(cmds->fd[cmds->cpipe - 1], 2);
        close_pipe(cmds->fd[cmds->cpipe], 1);
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
        if (dup_pipes(cmds) == -1)
            return (perror("Failed to dup pipes"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
        close_pipe(cmds->fd[cmds->cpipe], 2);
        waitpid(cid, NULL, 0);
    }
}

void    execute_binary(t_commands *cmds)
{
    if (cmds->nscmds == 1)
{        return (execute_one(cmds));
}	if (cmds->nscmds == 2 && cmds->npipes == 1)
	{
		while (cmds->ccmd < cmds->nscmds)
		{
			execute_one_pipe(cmds);
			cmds->ccmd++;
		}
		return ;
	}
    while (cmds->ccmd < cmds->nscmds - 1)
    {
        execute_cmd(cmds);
        cmds->ccmd++;
		cmds->cpipe++;
    }
	cmds->cpipe--;
    execute_last(cmds);
}
