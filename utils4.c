/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:49 by hamad             #+#    #+#             */
/*   Updated: 2024/12/30 17:12:14 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will free the variables from ft_execute2().
 * @params t, y, u, s The variables to be freed.
 * @return Void.
*/
void	free_variables(char **t, char **y, char **u, char **s)
{
	if (t)
		free_split(t);
	if (y)
		free_split(y);
	if (u)
		free_split(u);
	if (s)
		free_split(s);
}
/**
 * @brief This function will execute the command from the PATH variable.
 * @param cmds The commands structure.
 * @return Void.
 */
void	normal_execution(t_commands *cmds)
{
	int		i;
	char	**scmd;

	scmd = extract_command(cmds);
	if (!scmd)
		return (perror("Failed to extract the command."), exit(EF));
	i = 0;
	while (cmds->bpath[i] && ft_execute(cmds->bpath[i], scmd))
		i++;
	free_split(scmd);
	if (i == count_tokens(cmds->bpath))
		perror("");
}

void	child_functions(t_commands *cmds)
{
	if (ft_strcmp(cmds->c[cmds->cc][0], ECHO_COMMAND))
		builtin_echo(cmds);
	else if (ft_strcmp(cmds->c[cmds->cc][0], PWD_COMMAND))
		builtin_pwd();
	// else if (ft_strcmp(cmds->c[cmds->cc][0], ENV_COMMAND))
	// 	builtin_env(cmds);
	else
		normal_execution(cmds);
}

/**
 * @brief This function execute the builtin commands that should be executed
 * by the parent process.
 * @param cmds The commands structure.
 * @return Void.
 */
int	parent_functions(t_commands *cmds)
{
	if (ft_strcmp(cmds->c[cmds->cc][0], EXIT_COMMAND))
		return (builtin_exit(cmds), 1);
	else if (ft_strcmp(cmds->c[cmds->cc][0], CD_COMMAND))
		return (builtin_cd(cmds), 1);
	// else if (ft_strcmp(cmds->c[cmds->cc][0], EXPORT_COMMAND))
	// 	return (builtin_export(cmds), 1);
	// else if (ft_strcmp(cmds->c[cmds->cc][0], UNSET_COMMAND))
	// 	return (builtin_unset(NULL, NULL), 1);
	return (0);
}
