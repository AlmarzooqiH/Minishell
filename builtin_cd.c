/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:50:03 by hamad             #+#    #+#             */
/*   Updated: 2025/01/24 18:00:02 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/**
 * @brief This function will change the current directory to the home directory.
 * @param cmds The commands structure.
 * @return Void.
 */
void	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) != 0)
			return (perror("cd"));
	}
	else
		return (perror("cd: HOME not set\n"));
}

/**
 * @brief This function will change the current directory to the previous one.
 * @param cmds The commands structure.
 * @return Void.
 */
void	cd_previous(t_commands *cmds)
{
	if (cmds->previous_dir)
	{
		if (chdir(cmds->previous_dir) != 0)
			return (perror("cd"));
		else
			printf("%s\n", cmds->previous_dir);
	}
	else
		perror("cd: No previous directory");
}

/**
 * @brief This function will change the current directory to the desired one.
 * @param cmds The commands structure.
 * @return Void.
 */
void	cd_change_directory(t_commands *cmds)
{
	if (ft_contains(cmds->c[cmds->cc][1], '$'))
	{
		if (chdir(expand_variable(cmds, cmds->c[cmds->cc][1])) != 0)
			return (gs_status(GET_STATUS, SET_STATUS), perror("cd"));
		gs_status(SET_STATUS, SET_STATUS);
		return ;
	}
	{
		if (chdir(cmds->c[cmds->cc][1]) != 0)
			return (gs_status(GET_STATUS, SET_STATUS), perror("cd"));
		gs_status(SET_STATUS, SET_STATUS);
		return ;
	}
	if (chdir(cmds->c[cmds->cc][1]) != 0)
		return (gs_status(GET_STATUS, SET_STATUS), perror("cd"));
	gs_status(SET_STATUS, SET_STATUS);
}

/**
 * @brief This function will simulate the behavior of the cd command in bash.
 * @param cmds The commands structure.
 * @return Void.
 */
void	builtin_cd(t_commands *cmds)
{
	char	*current_dir;

	if (count_tokens(cmds->c[cmds->cc]) == 1)
		return (cd_home());
	current_dir = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!current_dir)
		return (perror("current_dir"));
	if (getcwd(current_dir, BUFFER_SIZE) != NULL)
	{
		if (cmds->previous_dir)
			free(cmds->previous_dir);
		cmds->previous_dir = ft_strdup(current_dir);
	}
	cd_change_directory(cmds);
	free(current_dir);
}
