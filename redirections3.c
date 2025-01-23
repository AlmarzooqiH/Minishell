/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:56:50 by hamad             #+#    #+#             */
/*   Updated: 2025/01/23 15:17:43 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	dup_heredoc(t_commands *cmds)
{
	cmds->rd[cmds->cc][cmds->hdp] = open(TEMP_FILE, O_RDONLY, PERMS);
	if (dup2(cmds->rd[cmds->cc][cmds->hdp], SIN) == -1)
		return (perror("Failed to dup2(hdr, SIN)"), exit(EF));
	close(cmds->rd[cmds->cc][cmds->hdp]);
}

void	ifp(t_commands *cmds)
{
	int	i;

	if (!cmds->fd || !cmds->rd)
		return ;
	i = 0;
	while (i < count_tokens(cmds->c[cmds->cc]))
	{
		if (cmds->rd[cmds->cc][i] == -1)
		{
			i++;
			continue ;
		}
		if (cmds->rd[cmds->cc][i] == e_rti)
			cmds->rtip = cmds->cfd;
		i++;
		increment(cmds, i);
	}
}
