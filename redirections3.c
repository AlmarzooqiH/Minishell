/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamad <hamad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:56:50 by hamad             #+#    #+#             */
/*   Updated: 2025/01/14 15:57:05 by hamad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	dup_heredoc(t_commands *cmds)
{
	cmds->rd[cmds->cc][cmds->hdp] = open(TEMP_FILE, O_RDONLY, PERMS);
	if (dup2(cmds->rd[cmds->cc][cmds->hdp], SIN) == -1)
		return (perror("Failed to dup2(hdr, SIN)"), exit(EF));
}
