/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:07:06 by mthodi            #+#    #+#             */
/*   Updated: 2025/01/01 20:07:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void print_envp(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        printf("declare -x %s\n", envp[i]);
        i++;
    }
}

int is_valid_identifier(t_commands *cmds, int i)
{
    if (!isalpha(cmds->c[cmds->cc][i][0]) && cmds->c[cmds->cc][i][0] != '_')
        return (0);
    int j = 1;
    while (cmds->c[cmds->cc][i][j] && cmds->c[cmds->cc][i][j] != '=')
    {
        if (!isalnum(cmds->c[cmds->cc][i][j]) && cmds->c[cmds->cc][i][j] != '_')
            return (0);
        j++;
    }
    return (1);
}

void update_envp(t_commands *cmds, int i)
{
    int j = 0;
    while (cmds->envp[j])
    {
        if (ft_strncmp(cmds->c[cmds->cc][i], cmds->envp[j], ft_strlen(cmds->c[cmds->cc][i])) == 0)
        {
            free(cmds->envp[j]);
            cmds->envp[j] = ft_strdup(cmds->c[cmds->cc][i]);
            return;
        }
        j++;
    }
    cmds->envp[j] = ft_strdup(cmds->c[cmds->cc][i]);
    cmds->envp[j + 1] = NULL;
}

void builtin_export(t_commands *cmds)
{
    int i = 1;
    while (cmds->c[cmds->cc][i])
    {
        if (!is_valid_identifier(cmds, i))
        {
            printf("export: `%s': not a valid identifier\n", cmds->c[cmds->cc][i]);
            cmds->es = 1;
        }
        else
            update_envp(cmds, i);
        i++;
    }
    cmds->es = 0;
}
