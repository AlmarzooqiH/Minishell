/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:58:24 by hamad             #+#    #+#             */
/*   Updated: 2024/12/31 14:06:17 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief This function will search for the enviorment variable and print it.
 * @param cmds The commands structure.
 * @param pos The position of the word.
 * @return Void.
 */
void	print_env(t_commands *cmds, int pos)
{
	int		i;
	char	*tmp;
	char	*env;

	tmp = ft_substr(cmds->c[cmds->cc][pos], 1,
			ft_strlen(cmds->c[cmds->cc][pos]));
	if (!tmp)
		return (perror("Failed to extract the tmp variable."));
	env = ft_strtrim(tmp, "\"");
	if (!env)
		return (perror("Failed to extract the env variable."));
	i = 0;
	while (cmds->envp[i])
	{
		if (ft_isprefix(cmds->envp[i], env))
		{
			printf("%s", ft_strchr(cmds->envp[i], '=') + 1);
			break ;
		}
		i++;
	}
	free(env);
	free(tmp);
}

/**
 * @brief This function will print the string and if there was passed some env
 * variables it will print them.
 * @param cmds The commands structure.
 * @param i The pointer of the current word.
 * @return Void.
 * @note This will be called if the input was like this: echo "path is: $PATH"
 */
void	print_double_quotes(t_commands *cmds, int *i)
{
	int	j;
	int	flag;

	j = 1;
	flag = 0;
	while (cmds->c[cmds->cc][*i])
	{
		if (flag)
			j = 0;
		while (cmds->c[cmds->cc][*i][j] && cmds->c[cmds->cc][*i][j] != '\"')
		{
			if (cmds->c[cmds->cc][*i][j] == '$')
			{
				print_env(cmds, *i);
				break ;
			}
			else
				printf("%c", cmds->c[cmds->cc][*i][j]);
			j++;
		}
		flag = 1;
		printf(" ");
		(*i)++;
	}
}

/**
 * @brief This function will print the string literal.
 * @param cmds The commands structure.
 * @param i The pointer of the current word.
 * @return Void.
 * @note This will be called if the input was like this: echo 'hello world'.
 */
void	print_literal(t_commands *cmds, int *i)
{
	int	j;
	int	flag;

	j = 1;
	flag = 0;
	while (cmds->c[cmds->cc][*i])
	{
		if (flag)
			j = 0;
		while (cmds->c[cmds->cc][*i][j] && cmds->c[cmds->cc][*i][j] != '\'')
		{
			printf("%c", cmds->c[cmds->cc][*i][j]);
			j++;
		}
		flag = 1;
		printf(" ");
		(*i)++;
	}
}

/**
 * @brief This function will print the normal string.
 * @param cmds The commands structure.
 * @param i The pointer of the current word.
 * @return Void.
 * @note This will be called if the input was like this: echo hello world.
 */
void	normal_print(t_commands *cmds, int *i)
{
	int	j;

	j = 0;
	while (cmds->c[cmds->cc][*i][j])
	{
		if (cmds->c[cmds->cc][*i][j] == '$')
		{
			print_env(cmds, *i);
			break ;
		}
		else
			printf("%c", cmds->c[cmds->cc][*i][j]);
		j++;
	}
	(*i)++;
	printf(" ");
}

/**
 * @brief This function will replicate the behavior of the echo command.
 * @param cmds The commands structure.
 * @return Void.
 */
void	builtin_echo(t_commands *cmds)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (ft_strcmp(cmds->c[cmds->cc][i], NL_FLAG))
	{
		n_flag = 1;
		i++;
	}
	while (cmds->c[cmds->cc][i])
	{
		if (cmds->c[cmds->cc][i][0] == '\'')
			print_literal(cmds, &i);
		else if (cmds->c[cmds->cc][i][0] == '\"')
			print_double_quotes(cmds, &i);
		else
			normal_print(cmds, &i);
	}
	if (!n_flag)
		printf("\n");
}