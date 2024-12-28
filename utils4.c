/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:49 by hamad             #+#    #+#             */
/*   Updated: 2024/12/28 23:55:18 by hamad            ###   ########.fr       */
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

/**
 * @brief This function will check if the command is a builtin. If not it will
 * call normal_execution() to execute the command from the PATH variable.
 * @param cmds The commands structure.
 * @return Void.
 */
void	is_builtin(t_commands *cmds)
{
	// if (ft_strcmp(cmds->cmds[cmds->cc][0], ECHO_COMMAND))
	// 	builtin_echo(cmds);
	if (ft_strcmp(cmds->cmds[cmds->cc][0], CD_COMMAND))
		builtin_cd(cmds);
	else if (ft_strcmp(cmds->cmds[cmds->cc][0], PWD_COMMAND))
		builtin_pwd();
	else if (ft_strcmp(cmds->cmds[cmds->cc][0], EXPORT_COMMAND))
		builtin_export(NULL, NULL);
	else if (ft_strcmp(cmds->cmds[cmds->cc][0], UNSET_COMMAND))
		builtin_unset(NULL, NULL);
	// else if (ft_strcmp(cmds->cmds[cmds->cc][0], ENV_COMMAND))
	// 	builtin_env(cmds);
	else if (ft_strcmp(cmds->cmds[cmds->cc][0], EXIT_COMMAND))
		builtin_exit(NULL, NULL);
	else
		normal_execution(cmds);
}
