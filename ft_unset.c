/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:36:32 by mthodi            #+#    #+#             */
/*   Updated: 2024/10/01 20:36:33 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to find the environment variable index
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

// Helper function to get the size of the environment
int	get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

// Helper function to reallocate and remove an environment variable
char	**realloc_env_unset(char **envp, int remove_idx, int env_size)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * env_size);  // Reduced size
	if (!new_envp)
		return (NULL);
	while (i < env_size)
	{
		if (i != remove_idx)
			new_envp[j++] = envp[i];
		else
			free(envp[i]);  // Free the variable to be unset
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

// Unset an environment variable
int	ft_unset(char *var, char ***envp)
{
	int		idx;
	int		env_size;
	char	**new_envp;

	env_size = get_env_size(*envp);
	idx = find_env_var(var, *envp);
	if (!var)  // No valid variable to unset
		return (1);
	if (idx != -1)
	{
		new_envp = realloc_env_unset(*envp, idx, env_size);
		if (!new_envp)
			return (1);  // Memory allocation failure
		*envp = new_envp;
	}
	return (0);
}
/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:36:32 by mthodi            #+#    #+#             */
/*   Updated: 2024/10/01 20:36:33 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Helper function to find the environment variable index
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

// Helper function to get the size of the environment
int	get_env_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

// Helper function to reallocate and remove an environment variable
char	**realloc_env_unset(char **envp, int remove_idx, int env_size)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * env_size);  // Reduced size
	if (!new_envp)
		return (NULL);
	while (i < env_size)
	{
		if (i != remove_idx)
			new_envp[j++] = envp[i];
		else
			free(envp[i]);  // Free the variable to be unset
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

// Unset an environment variable
int	ft_unset(char *var, char ***envp)
{
	int		idx;
	int		env_size;
	char	**new_envp;

	env_size = get_env_size(*envp);
	idx = find_env_var(var, *envp);
	if (!var)  // No valid variable to unset
		return (1);
	if (idx != -1)
	{
		new_envp = realloc_env_unset(*envp, idx, env_size);
		if (!new_envp)
			return (1);  // Memory allocation failure
		*envp = new_envp;
	}
	return (0);
}
