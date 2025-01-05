/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:46:52 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/05 17:04:56 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*extract_env_name(const char *str)
{
	char	*tmp;
	char	*env;

	tmp = ft_substr(str, 1, ft_strlen(str));
	if (!tmp)
		return (NULL);
	env = ft_strtrim(tmp, "$\"");
	free(tmp);
	if (!env)
		return (NULL);
	return (env);
}

char	*find_env_value(t_commands *cmds, const char *env)
{
	int		i;
	char	*value;
	char	*equal_sign;

	if (!cmds || !cmds->envp || !env)
		return (NULL);
	i = 0;
	value = NULL;
	while (cmds->envp[i])
	{
		equal_sign = ft_strchr(cmds->envp[i], '=');
		if (equal_sign && ft_isprefix(cmds->envp[i], env)
			&& cmds->envp[i][ft_strlen(env)] == '=')
		{
			value = ft_strdup(equal_sign + 1);
			break ;
		}
		i++;
	}
	return (value);
}

int	handle_n_flag(t_commands *cmds, int *index)
{
	if (ft_strcmp(cmds->c[cmds->cc][*index], NL_FLAG))
	{
		(*index)++;
		return (1);
	}
	return (0);
}

void	process_echo_argument(t_commands *cmds, const char *arg)
{
	int		arg_index;
	char	first_char;

	arg_index = 0;
	while (cmds->c[cmds->cc][arg_index]
		&& cmds->c[cmds->cc][arg_index] != (char *)arg)
		arg_index++;
	if (!is_valid_quoted_part(cmds->c[cmds->cc], arg_index))
	{
		print_quote_error(arg);
		return ;
	}
	first_char = arg[0];
	if (first_char == '\'' )
		print_single_quoted_content(arg);
	else if (first_char == '\"')
		print_double_quoted_content(cmds, arg);
	else
		print_normal_text(cmds, arg);
}
