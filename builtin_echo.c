/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:51:55 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/05 19:36:40 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will search for and expand environment variables.
 * @param cmds The commands structure.
 * @param str The string containing the environment variable.
 * @return Allocated string containing the expanded 
 * 		value or empty string if env var doesn't exist.
 */

char	*expand_env(t_commands *cmds, const char *str)
{
	char	*env;
	char	*value;

	env = extract_env_name(str);
	if (!env)
		return (NULL);
	value = find_env_value(cmds, env);
	free(env);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

/**
 * @brief Print content between double quotes, expanding env vars
 * @param cmds Command structure
 * @param str String to process
 * int i = 1 skips the first quote
 */
void	print_double_quoted_content(t_commands *cmds, const char *str)
{
	int		i;
	char	*value;

	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '\"')
		{
			value = expand_env(cmds, str + i);
			if (value)
			{
				printf("%s", value);
				free(value);
				while (str[i + 1] && str[i + 1]
					!= '\"' && str[i + 1] != '$')
					i++;
			}
		}
		else
			printf("%c", str[i]);
		i++;
	}
}

/**
 * @brief Print content between single quotes (literal)
 * @param str String to process
 * int i = 1 skips the first quote
 */
void	print_single_quoted_content(const char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
	{
		printf("%c", str[i]);
		i++;
	}
}

/**
 * @brief Print normal text, handling environment variables
 * @param cmds Command structure
 * @param str String to process
 */
void	print_normal_text(t_commands *cmds, const char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			value = expand_env(cmds, str + i);
			if (value)
			{
				printf("%s", value);
				free(value);
				while (str[i + 1] && str[i + 1]
					!= ' ' && str[i + 1] != '$')
					i++;
			}
		}
		else
			printf("%c", str[i]);
		i++;
	}
}

/**
 * @brief Echo command implementation
 * @param cmds Command structure
 */
void	builtin_echo(t_commands *cmds)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = handle_n_flag(cmds, &i);
	while (cmds->c[cmds->cc][i])
	{
		process_echo_argument(cmds, cmds->c[cmds->cc][i]);
		if (cmds->c[cmds->cc][i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
