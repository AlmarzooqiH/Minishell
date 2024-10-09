/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:26:54 by mthodi            #+#    #+#             */
/*   Updated: 2024/10/08 16:21:41 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to check if the variable already exists in the environment
int	find_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);  // Not found
}

// Helper function to calculate the size of the environment array
int	get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

// Helper function to reallocate environment array and add a new variable
char	**realloc_env(char **envp, char *var, int env_size)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (env_size + 2));  // Extra space for new var
	if (!new_envp)
		return (NULL);  // Handle memory allocation failure
	while (i < env_size)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[env_size] = ft_strdup(var);
	new_envp[env_size + 1] = NULL;
	return (new_envp);
}

// Add or modify an environment variable
int	builtin_export(char *var, char ***envp)
{
	int		idx;
	int		env_size;
	char	**new_envp;

	idx = find_env_var(var, *envp);
	if (!var || !ft_strchr(var, '='))  // No valid variable to export
		return (1);
	env_size = get_env_size(*envp);
	if (idx != -1)
	{
		free((*envp)[idx]);
		(*envp)[idx] = ft_strdup(var);
	}
	else
	{
		new_envp = realloc_env(*envp, var, env_size);
		if (!new_envp)
			return (1);  // Memory allocation failure
		*envp = new_envp;
	}
	return (0);
}
