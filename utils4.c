/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:49 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 18:10:01 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will execute the command from the PATH variable.
 * @param cmds The commands structure.
 * @return Void.
 */

void	normal_execution(t_commands *cmds)
{
	int		i;
	char	**bpath;
	char	**scmd;
	int		pidx;

	scmd = extract_command(cmds);
	if (!scmd)
		return (perror(FTESC), exit(EF));
	pidx = get_path(cmds->envp);
	if (pidx == -1)
		return (perror(PVNF), free_tings(cmds, scmd, NULL), exit(EF));
	bpath = ft_split(cmds->envp[pidx] + 5, ':');
	if (!bpath)
		return (perror(FTPTPV), free_tings(cmds, scmd, bpath), exit(EF));
	i = 0;
	while (bpath[i] && ft_execute(bpath[i], scmd, cmds->envp))
		i++;
	if (ft_strcmp(cmds->c[cmds->cc][0], "$?") && i == count_tokens(bpath))
		return (printf("%d: Command not found\n", gs_status(0, GET_STATUS)),
			free_tings(cmds, scmd, bpath), exit(127));
	if (i == count_tokens(bpath))
		return (perror("Command not found"), free_tings(cmds, scmd, bpath),
			exit(127));
	return (free_tings(cmds, scmd, bpath), exit(ES));
}

/**
 * @brief This function will check if the current command is a builtin command
 * and it's output can be piped to another command.
 * @param cmds The commands structure.
 * @return Void.
 */
void	child_functions(t_commands *cmds)
{
	if (ft_strcmp(cmds->c[cmds->cc][0], ECHO_COMMAND))
		builtin_echo(cmds);
	else if (ft_strcmp(cmds->c[cmds->cc][0], PWD_COMMAND))
		builtin_pwd();
	else if (ft_strcmp(cmds->c[cmds->cc][0], ENV_COMMAND)
		&& cmds->c[cmds->cc][1] == NULL)
		builtin_env(cmds);
	else
		normal_execution(cmds);
}

/**
 * @brief This function execute the builtin commands that should be executed
 * by the parent process.
 * @param cmds The commands structure.
 * @return 0 on failure 1 on success.
 */
int	parent_functions(t_commands *cmds)
{
	if (ft_strcmp(cmds->c[cmds->cc][0], EXIT_COMMAND))
		return (builtin_exit(cmds), 1);
	else if (ft_strcmp(cmds->c[cmds->cc][0], CD_COMMAND))
		return (builtin_cd(cmds), 1);
	else if (ft_strcmp(cmds->c[cmds->cc][0], UNSET_COMMAND))
		return (builtin_unset(cmds), 1);
	else if (ft_strcmp(cmds->c[cmds->cc][0], EXPORT_COMMAND))
		return (builtin_export(cmds), 1);
	return (0);
}

/**
 * @brief This function will check if the command is a builtin command.
 * @param cmds The commands structure.
 * @return Void.
 */
void	isbuiltin(t_commands *cmds)
{
	if (ft_strcmp(cmds->c[cmds->cc][0], ECHO_COMMAND) ||
		ft_strcmp(cmds->c[cmds->cc][0], PWD_COMMAND) ||
		ft_strcmp(cmds->c[cmds->cc][0], ENV_COMMAND))
		cmds->bltin = 1;
}

void	close_fd(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->nre)
	{
		if (cmds->fd[i] >= 0)
			cmds->fd[i] = -1;
		i++;
	}
}
