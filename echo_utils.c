/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:41:14 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/21 09:41:21 by mthodi           ###   ########.fr       */
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
int	process_env_var(char *str, int j)
{
	int		var_len;
	char	*var_name;
	char	*var;
	char	*env_value;

	var_name = &str[j];
	var_len = 0;
	while (var_name[var_len] && (ft_isalnum(var_name[var_len])
			|| var_name[var_len] == '_'))
		var_len++;
	var = malloc(var_len + 1);
	if (!var)
		return (perror("malloc"), 0);
	ft_strlcpy(var, var_name, var_len + 1);
	env_value = getenv(var);
	if (env_value)
		printf("%s", env_value);
	free(var);
	return (var_len);
}
