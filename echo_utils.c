/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:41:14 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/30 17:45:36 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will print the string and if there was passed some env
 * variables it will print them.
 * @param cmds The commands structure.
 * @param i The pointer of the current word.
 * @return Void.
 * @note This will be called if the input was like this: echo "path is: $PATH"
 */
int	process_env_var(t_commands *cmds, char *str, int j)
{
	int		var_len;
	char	*var;
	int		i;

	var_len = 0;
	while (str[j + var_len] && (ft_isalnum(str[j + var_len])
			|| str[j + var_len] == '_'))
		var_len++;
	var = malloc(var_len + 1);
	if (!var)
		return (perror("malloc"), 0);
	ft_strlcpy(var, &str[j], var_len + 1);
	i = 0;
	while (cmds->envp[i])
	{
		if (ft_exp_isprefix(cmds->envp[i], var))
		{
			printf("%s", ft_strchr(cmds->envp[i], '=') + 1);
			free(var);
			return (var_len);
		}
		i++;
	}
	free(var);
	return (var_len);
}
