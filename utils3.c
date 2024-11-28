/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:29:52 by hamad             #+#    #+#             */
/*   Updated: 2024/11/25 22:33:42 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	while (cmds->cmds[i])
	{
		cmds->redir[i] = (int *)malloc(sizeof(int)
				* count_tokens(cmds->cmds[i]));
		if (!cmds->redir[i])
			return (free_cmds(cmds), perror("Failed to malloc redir"));
		j = 0;
		while (cmds->cmds[i][j])
		{
			cmds->redir[i][j] = is_redirection(cmds->cmds[i][j]);
			j++;
		}
		i++;
	}
}

/**
 * @brief	This function will check if the current sub command is in bash syn-
 * -tax or not. If it is true it will set the is_bash[i] array to 1 else to 0.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	set_isbash(t_commands *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->nscmds)
	{
		cmds->is_bash[i] = is_bashsyntax(cmds->cmds[i]);
		i++;
	}
}

/**
 * @brief 	This function will set the file names to the cmds->files array.
 * @param	cmds	This will holds the preprocessd command.
 * @return	void
 */
void	set_files(t_commands *cmds)
{
	int	c;
	int	t;
	int	f;

	c = 0;
	f = 0;
	while (cmds->cmds[c])
	{
		t = 0;
		while (cmds->cmds[c][t])
		{
			if (cmds->redir[c][t] >= 0)
			{
				if (is_alone(cmds->cmds[c][t]))
					cmds->files[f] = ft_strdup(cmds->cmds[c][++t]);
				else
					cmds->files[f] = gfn(cmds->cmds[c][t], cmds->redir[c][t]);
				if (!cmds->files[f++])
					return (free_cmds(cmds), perror("Failed to malloc files"));
			}
			t++;
		}
		c++;
	}
	cmds->files[f] = NULL;
}

void	print_struct(t_commands *cmds)
{
	int	i;

	printf("enviorment: %s\n", cmds->enviorment);
	printf("bpath:\n");
	print_split(cmds->bpath);
	printf("cmds:\n");
	i = 0;
	while (i < cmds->nscmds)
		print_split(cmds->cmds[i++]);
	printf("Files: \n");
	print_split(cmds->files);
	printf("is_bash:\n");
	i = 0;
	while (i < cmds->nscmds)
	{
		printf(" is_bash[%d]: %d\n", i, cmds->is_bash[i]);
		i++;
	}
	printf("Pipes\n");
	i = 0;
	while (i < cmds->npipes)
	{
		printf("Pipe[%d][0]: %d\nPipe[%d][1]: %d\n", i, cmds->fd[i][0], i, cmds->fd[i][1]);
		i++;
	}
}

/**
 * @brief This function will extract the command from the tokenized commands.
 * @param cmds  This holds the commands struct.
 * @return  The extracted command.
 */
char    **extract_command(t_commands *cmds)
{
    size_t  i;
    size_t  j;
    char **cmd;

    if (cmds->is_bash[cmds->ccmd] && is_alone(cmds->cmds[cmds->ccmd][0]))
        i = 2;
    else if (cmds->is_bash[cmds->ccmd] && !is_alone(cmds->cmds[cmds->ccmd][0]))
        i = 1;
    else
        i = 0;
    j = i;
    while (cmds->cmds[cmds->ccmd][i] && !(is_redirection(cmds->cmds[cmds->ccmd][i]) >= 0))
        i++;
    cmd = trim_command(ft_subnsplit(cmds->cmds[cmds->ccmd], j, i));
    return (cmd);    
}
