/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:23:52 by hamad             #+#    #+#             */
/*   Updated: 2025/02/01 16:52:34 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
	@brief This function will split the commands into sub strings that will be
			stored in an array.
	@param	command		The commands that was passed in by the user.
	@param	tokens		Here is where the commands will be stored.
	@param	split		The delimeter that we want to use to split the tokens.
	@var	temp		This will temporaraly hold the substring.
	@var	temp_split	This will hold the tokens that we split from the temp.
	@var	i			Will iterate through the string.
	@var	j			Will store the end of the substring.
	@var	k			Will be the position for the tokens.
*/
void	get_tokens(char *command, char ***tokens, char split)
{
	char	*temp;
	char	**temp_split;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (command[i])
	{
		j = i;
		get_end(command, split, &j);
		temp = ft_substr(command, i, j - i);
		if (!temp)
			break ;
		temp_split = get_command(temp);
		tokens[k++] = temp_split;
		free(temp);
		if (command[j] != '\0')
			i = j + 1;
		else
			i = j;
	}
	tokens[k] = NULL;
}

/*
	@brief				This function will free the tokens.
	@param	tokens		The tokens that we want to free.
	@param	n_tokens	The size of tokens param.
*/
void	free_tokens(char ***tokens, int n_tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return ;
	i = 0;
	while (i < n_tokens)
	{
		free_split(tokens[i]);
		i++;
	}
	free(tokens);
}

/*
	@brief				This function will take the commands and trim any \" t-
						-hat are in the commands so it can process them withou-
						-t any issues. e.g ls | grep -o "main" will be returne-
						-d as grep -o main.
	@param	commands	This will hold the commands passed by the user.
	@return				char ** with trimmed qoutes \".
*/
char	**trim_command(char	**commands)
{
	char	**new;
	char	*tmp;
	size_t	i;
	size_t	size;

	if (!commands || !commands[0])
		return (NULL);
	size = count_split(commands);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tmp = ft_strtrim(commands[i], "\"\'");
		if (!tmp)
			return (free_split(new), NULL);
		new[i] = tmp;
		i++;
	}
	new[i] = NULL;
	free_split(commands);
	commands = NULL;
	return (new);
}

/**
 * @brief	This function will extract the file name from the command.
 * @param	command	The command that contains the filename and redierction e.g.
 * 					<filename, we will substring it to filename only.
 * @param	redirection	This will tell us what redierction it is in.
 * @return	filename if successfull.
 * @return	NULL if failure.
 */
char	*gfn(char *command, int redirection)
{
	char	*filename;
	char	*tmp;
	size_t	i;

	if (!command)
		return (NULL);
	i = 0;
	if (redirection == e_rtf)
		i = 1;
	else if (redirection == e_rti)
		i = 1;
	else if (redirection == e_ar)
		i = 2;
	else if (redirection == e_hdr)
		i = 2;
	tmp = ft_substr(command, i, ft_strlen(command));
	if (!tmp)
		return (NULL);
	filename = ft_strtrim(tmp, "\"\'");
	if (!filename)
		return (NULL);
	if (tmp)
		free(tmp);
	return (filename);
}

/**
 * @brief	This function will sotre the type of the redirection in the redir
 * array.
 * @param	cmds	This will holds the processed commands.
 * @return	void
 */
void	set_redirectons(t_commands *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds->nscmds && cmds->c[i] != NULL)
	{
		cmds->rd[i] = (int *)ft_calloc(count_tokens(cmds->c[i]), sizeof(int));
		if (!cmds->rd[i])
			return (free_cmds(cmds), perror("Failed to malloc redir"));
		j = 0;
		while (j < count_tokens(cmds->c[i]) && cmds->c[i][j])
		{
			cmds->rd[i][j] = is_redirection(cmds->c[i][j]);
			j++;
		}
		i++;
	}
}
