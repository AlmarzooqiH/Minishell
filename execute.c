/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2024/12/19 15:05:07 by hamad            ###   ########.fr       */
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
		if (cmds->rd && has_redirection(cmds))
			return (process_redir(cmds), exit(ES));
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
		if (cmds->cc == 0)
			close(cmds->p[cmds->cp][1]);
		else if (cmds->cc == 1)
			close(cmds->p[cmds->cp][0]);
		waitpid(cid, NULL, 0);
	}
}

void	execute_one(t_commands *cmds)
{
	pid_t	cid;
	int		i;
	char	**scmd;

	cid = fork();
	if (!cid)
	{
		i = 0;
		if (has_redirection(cmds))
			return (process_redir(cmds), exit(ES));
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

void	execute_cmd(t_commands *cmds)
{
	pid_t	cid;
	int		i;
	char	**scmd;

	cid = fork();
	if (!cid)
	{
		printf("has_redirection: %d\n", has_redirection(cmds));
		if (cmds->rd && has_redirection(cmds))
			return (process_redir(cmds), exit(ES));
		i = 0;
		scmd = extract_command(cmds);
		if (!scmd)
			return (perror("Failed to extract the command"), exit(EF));
		if (dup_pipes(cmds) == -1)
			return (perror("Failed to dup pipes"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
		if (cmds->cp > 0)
			return (waitpid(cid, NULL, 0), cpipe(cmds->p[cmds->cp - 1], 2));
		return (waitpid(cid, NULL, 0), cpipe(cmds->p[cmds->cp], 1));
	}
}

void	execute_last(t_commands *cmds)
{
	pid_t	cid;
	int		i;
	char	**scmd;

	cid = fork();
	if (!cid)
	{
		i = 0;
		if (has_redirection(cmds))
			return (process_redir(cmds), exit(ES));
		scmd = extract_command(cmds);
		if (!scmd)
			return (perror("Failed to extract the command"), exit(EF));
		if (dup_pipes(cmds) == -1)
			return (perror("Failed to dup pipes"), exit(EF));
		while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
			i++;
		free_split(scmd);
	}
	else if (cid > 0)
	{
		cpipe(cmds->p[cmds->cp], 2);
		waitpid(cid, NULL, 0);
	}
}

void	execute_binary(t_commands *cmds)
{
	if (cmds->nscmds == 1)
		return (execute_one(cmds));
	if (cmds->nscmds == 2 && cmds->npipes == 1)
	{
		while (cmds->cc < cmds->nscmds)
		{
			execute_one_pipe(cmds);
			cmds->cc++;
		}
		return ;
	}
	while (cmds->cc < cmds->nscmds - 1)
	{
		execute_cmd(cmds);
		cmds->cc++;
		cmds->cp++;
	}
	cmds->cp--;
	execute_last(cmds);
}
