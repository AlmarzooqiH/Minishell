/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:56:57 by mthodi            #+#    #+#             */
/*   Updated: 2024/10/08 16:23:04 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**duplicate_env(char **envp)
{
	int		count;
	int		i;
	int		j;
	char	**env_copy;

	count = 0;
	while (envp[count]) // Count the number of environment variables using a while loop
		count++;
	env_copy = malloc((count + 1) * sizeof(char *)); // Allocate memory for the copy
	if (!env_copy)
		return NULL; // Handle allocation failure
	i = 0;
	while (++i < count) // Use a while loop to duplicate each string
	{
		env_copy[i] = strdup(envp[i]); // Duplicate each string
		if (!env_copy[i])
		{
			j = 0;// Handle allocation failure, free previously allocated strings
			while (j < i)
				free(env_copy[j++]); // Free previously allocated strings
			return (free(env_copy), NULL);
		}
	}
	env_copy[count] = NULL; // Null-terminate the array
	return (env_copy);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ; // Check for null pointer
	// Use a while loop to free each duplicated string
	while (env[i])
	{
		free(env[i]); // Free each string
		i++;
	}
	free(env); // Finally, free the array itself
}
