/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:20 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/12 14:34:30 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/**
 * @brief Check if a string starts with an opening quote
 * @param str The string to check
 * @return The quote character if found, 0 otherwise
 */
char	is_opening_quote(const char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '"' || str[0] == '\'')
		return (str[0]);
	return (0);
}

/**
 * @brief Check if a string ends with a closing quote
 * @param str The string to check
 * @param quote_char The type of quote to look for
 * @return 1 if string ends with matching quote, 0 otherwise
 */
int	is_closing_quote(const char *str, char quote_char)
{
	int	len;

	if (!str || !quote_char)
		return (0);
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	return (str[len - 1] == quote_char);
}

/**
 * @brief Check if string is a middle part of a quoted string
 * @param str The string to check
 * @return 1 if it's a middle part, 0 otherwise
 */
int	is_middle_of_quote(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			print_quote_error(str);
			return (0);
		}
		i++;
	}
	return (!is_opening_quote(str) && !is_closing_quote(str, '"')
		&& !is_closing_quote(str, '\''));
}

/**
 * @brief Checks if this argument is part of a valid quoted string
 * @param cmd The command array
 * @param current_index The index of current argument
 * @return 1 if valid, 0 if not
 */
int	is_valid_quoted_part(char **cmd, int current_index)
{
	char	quote_char;
	int		found_opening;
	int		found_closing;

	if (!cmd || !cmd[current_index])
		return (0);
	quote_char = 0;
	found_opening = find_opening_quote(cmd, current_index, &quote_char);
	if (!found_opening)
		return (1);
	found_closing = find_closing_quote(cmd, current_index, quote_char);
	return (found_opening && found_closing);
}

/**
 * @brief Print error message for unclosed quotes
 * @param arg The argument containing unclosed quotes
 */
void	print_quote_error(const char *arg)
{
	char	*error_prefix;
	char	*error_suffix;
	char	*arg_copy;

	error_prefix = ft_strdup("minishell: echo: error: unclosed quotes in '");
	error_suffix = ft_strdup("'\n");
	arg_copy = ft_strdup(arg);
	if (error_prefix && error_suffix && arg_copy)
	{
		ft_putstr_fd(error_prefix, 2);
		ft_putstr_fd(arg_copy, 2);
		ft_putstr_fd(error_suffix, 2);
	}
	free(error_prefix);
	free(error_suffix);
	free(arg_copy);
}
