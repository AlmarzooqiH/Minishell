/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:38:22 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 15:32:33 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will execute the commands that have one pipe only.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	execute_one_pipe(t_commands *cmds)
{
	pid_t	cid;
	int		exit_code;

	exit_code = 0;
	if (parent_functions(cmds))
		return ;
	cid = fork();
	if (!cid)
	{
		if (cmds->rd && has_redirection(cmds))
			return (predir(cmds), exit(ES));
		if (dup_pipes(cmds) == -1)
			return (perror("Failed to dup pipes"), free_tings(cmds, NULL, NULL), exit(EF));
		return (child_functions(cmds), free(cmds), gs_envp(NULL, EXIT_ENVP),
			free_cmds(cmds), exit(ES));
	}
	else if (cid > 0)
	{
		waitpid(cid, &exit_code, 0);
		if (cmds->cc == 0 && cmds->p[cmds->cp][1] >= 0)
			cp(cmds->p[cmds->cp], 1);
		else if (cmds->cc == 1 && cmds->p[cmds->cp][0] >= 0)
			cp(cmds->p[cmds->cp], 0);
		return (gs_status((exit_code >> 8), SET_STATUS), ifp(cmds));
	}
}

/**
 * @brief This function will execute one command only.
 * @param cmds This holds the commands struct.
 * @return Void.
 * @note This will be called if cmds->nscmds == 1.
 */
void	execute_one(t_commands *cmds)
{
	pid_t	cid;
	int		exit_code;

	exit_code = 0;
	if (parent_functions(cmds))
		return ;
	cid = fork();
	if (!cid)
	{
		if (has_redirection(cmds))
			return (predir(cmds), free_tings(cmds, NULL, NULL), exit(ES));
		child_functions(cmds);
		free_cmds(cmds);
		free(cmds);
		gs_envp(NULL, EXIT_ENVP);
		exit(ES);
	}
	else if (cid > 0)
		waitpid(cid, &exit_code, 0);
	gs_status((exit_code >> 8), SET_STATUS);
	ifp(cmds);
}

/**
 * @brief This function will execute the commands inbetween the first and the
 * last command.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	execute_cmd(t_commands *cmds)
{
	pid_t	cid;
	int		exit_code;

	exit_code = 0;
	if (parent_functions(cmds))
		return ;
	cid = fork();
	if (!cid)
	{
		if (cmds->rd && has_redirection(cmds))
			return (predir(cmds), free_tings(cmds, NULL, NULL), exit(ES));
		if (dup_pipes(cmds) == -1)
			return (perror("Failed to dup pipes"), free_tings(cmds, NULL, NULL),
				exit(EF));
		return (child_functions(cmds), free(cmds), gs_envp(NULL, EXIT_ENVP),
			free_cmds(cmds), exit(ES));
	}
	else if (cid > 0)
	{
		waitpid(cid, &exit_code, 0);
		if (cmds->cp > 0)
			cp(cmds->p[cmds->cp - 1], 2);
		cp(cmds->p[cmds->cp], 1);
		return (gs_status((exit_code >> 8), SET_STATUS), ifp(cmds));
	}
}

/**
 * @brief This function will execute the last command.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	execute_last(t_commands *cmds)
{
	pid_t	cid;
	int		exit_code;

	exit_code = 0;
	if (parent_functions(cmds))
		return ;
	cid = fork();
	if (!cid)
	{
		if (has_redirection(cmds))
			return (predir(cmds),
				free_tings(cmds, NULL, NULL), exit(ES));
		if (dup_pipes(cmds) == -1)
			return (perror("Failed to dup pipes"), exit(EF));
		return (child_functions(cmds), free(cmds), gs_envp(NULL, EXIT_ENVP),
			free_cmds(cmds), exit(ES));
	}
	else if (cid > 0)
	{
		waitpid(cid, &exit_code, 0);
		cp(cmds->p[cmds->cp], 2);
		gs_status((exit_code >> 8), SET_STATUS);
		ifp(cmds);
	}
}

/**
 * @brief This function is responsible for executing the commands.
 * @param cmds This holds the commands struct.
 * @return Void.
 */
void	execute_binary(t_commands *cmds)
{
	if (cmds->nscmds == 1)
		return (execute_one(cmds), init_signals());
	if (cmds->nscmds == 2 && cmds->npipes == 1)
	{
		while (cmds->cc < cmds->nscmds)
		{
			isbuiltin(cmds);
			execute_one_pipe(cmds);
			cmds->cc++;
			cmds->bltin = 0;
			init_signals();
		}
		return ;
	}
	while (cmds->cc < cmds->nscmds - 1)
	{
		init_signals();
		isbuiltin(cmds);
		execute_cmd(cmds);
		cmds->cc++;
		cmds->cp++;
		cmds->bltin = 0;
		init_signals();
	}
	return (isbuiltin(cmds), cmds->cp--, execute_last(cmds));
}
