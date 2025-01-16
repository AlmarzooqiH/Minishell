/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:00:06 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/16 17:00:16 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Process quote character for space checking
 * @param c Current character
 * @param in_quotes Pointer to quote state
 * @param quote_char Pointer to quote character
 */
void	process_space_quote(char c, t_quote_info *info)
{
	if (!info->in_quotes)
	{
		info->in_quotes = 1;
		info->quote_char = c;
	}
	else if (c == info->quote_char)
	{
		info->in_quotes = 0;
		info->quote_char = 0;
	}
}
