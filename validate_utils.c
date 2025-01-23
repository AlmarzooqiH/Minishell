/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:09 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/23 14:36:05 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @brief Check if a token starts with a quote and find its closing quote
 * @param token The token to check
 * @param quote_char Pointer to store the quote character
 * @return 1 if token starts with quote, 0 otherwise
 */
int	starts_with_quote(char *token, char *quote_char)
{
	if (!token || !token[0])
		return (0);
	if (token[0] == '"' || token[0] == '\'')
	{
		*quote_char = token[0];
		return (1);
	}
	return (0);
}

/**
 * @brief Check if quote is closed within current token
 * @param token The token to check
 * @param quote_char The quote character to look for
 * @return 1 if quote is closed, 0 otherwise
 */
int	is_quote_closed_in_token(char *token, char quote_char)
{
	size_t	k;

	k = 1;
	while (token[k])
	{
		if (token[k] == quote_char)
			return (k == ft_strlen(token) - 1);
		k++;
	}
	return (0);
}

/**
 * @brief Look for closing quote in subsequent tokens
 * @param tokens Current command tokens
 * @param start_j Starting token index
 * @param i Current command index
 * @param quote_char Quote character to look for
 * @return 1 if quote is found, 0 otherwise
 */
int	find_closing_quote(char **tokens, int start_j, int i, char quote_char)
{
	int	temp_j;
	int	k;

	(void)i;
	temp_j = start_j;
	while (tokens[temp_j])
	{
		k = 0;
		while (tokens[temp_j][k])
		{
			if (tokens[temp_j][k] == quote_char)
				return (1);
			k++;
		}
		temp_j++;
	}
	return (0);
}

/**
 * @brief Validate quotes in a command segment
 * @param tokens Command tokens
 * @param i Command index
 * @param j Token index
 * @return 1 if valid, 0 if invalid
 */
int	validate_quotes(char ***tokens, int i, int j)
{
	char	quote_char;

	if (starts_with_quote(tokens[i][j], &quote_char))
	{
		if (is_quote_closed_in_token(tokens[i][j], quote_char))
			return (1);
		else if (!find_closing_quote(tokens[i], j, i, quote_char))
			return (perror(UQIC), 0);
	}
	return (1);
}

/**)
 * @brief Process a single command segment
 * @param tokens All command tokens
 * @param i Current command index
 * @param npipes Number of pipes
 * @return 1 if valid, 0 if invalid
 */
int	process_command_segment(char ***tokens, int i, int npipes)
{
	int	j;

	j = 0;
	if (!ciec(tokens, i, npipes))
		return (0);
	while (j < count_tokens(tokens[i]))
	{
		if (!validate_quotes(tokens, i, j))
			return (0);
		if (is_redirection(tokens[i][j]) >= 0 && !cife(tokens, &i, &j))
			return (0);
		j++;
	}
	return (1);
}
