/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:26:57 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/23 20:16:11 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Skip leading whitespace in command
 * @param command The command string
 * @return Index after whitespace
 */
int	skip_whitespace(const char *command)
{
	int	i;

	i = 0;
	while (ft_isspace(command[i]))
		i++;
	return (i);
}

/**
 * @brief Initialize quote tracking variables
 * @param in_quotes Pointer to quote state
 * @param quote_char Pointer to current quote character
 * @param start_pos Pointer to quote start position
 */
void	init_quote_tracking(t_quote_info *info)
{
	info->in_quotes = 0;
	info->quote_char = 0;
	info->start_pos = -1;
}

/**
 * @brief Check if character is a quote
 * @param c Character to check
 * @return 1 if quote, 0 otherwise
 */
int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

/**
 * @brief Process quote character in command
 * @param c Current character
 * @param in_quotes Pointer to quote state
 * @param quote_char Pointer to current quote character
 * @param pos Current position
 * @param start_pos Pointer to quote start position
 */
void	process_quote(char c, t_quote_info *info, int pos)
{
	if (!info->in_quotes)
	{
		info->in_quotes = 1;
		info->quote_char = c;
		info->start_pos = pos;
	}
	else if (c == info->quote_char)
	{
		info->in_quotes = 0;
		info->quote_char = 0;
	}
}

/*
 * @brief Initialize quote tracking for space checking
 * @param command Command string
 * @param pos Position to check
 * @return 1 if input is valid, 0 otherwise
 */
int	init_space_check(const char *command, int pos)
{
	if (!command || pos < 0)
		return (0);
	return (1);
}
