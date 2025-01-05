/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:46 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/05 16:41:08 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Find the opening quote and its type
 * @param cmd The command array
 * @param current_index The index of the current argument
 * @param quote_char Pointer to store the quote character
 * @return 1 if opening quote is found, 0 otherwise
 */
int	find_opening_quote(char **cmd, int current_index, char *quote_char)
{
	int	i;

	i = current_index;
	while (i >= 0 && cmd[i])
	{
		if (is_opening_quote(cmd[i]))
		{
			*quote_char = cmd[i][0];
			return (1);
		}
		i--;
	}
	return (0);
}

/**
 * @brief Check for the closing quote
 * @param cmd The command array
 * @param current_index The index of the current argument
 * @param quote_char The type of quote to look for
 * @return 1 if closing quote is found, 0 otherwise
 */
int	find_closing_quote(char **cmd, int current_index, char quote_char)
{
	int	i;

	i = current_index;
	while (cmd[i])
	{
		if (is_closing_quote(cmd[i], quote_char))
			return (1);
		i++;
	}
	return (0);
}
