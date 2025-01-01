#include "includes/minishell.h"

/**
 * @brief Executes the env builtin command, printing the environment variables.
 * @param cmds The structure containing the parsed commands.
 * @param pos The starting position of the arguments for env.
 * @return Void.
 */

void	builtin_env(t_commands *cmds)
{
    int	i;

    i = 0;
    while (cmds->envp[i])
    {
        printf("%s\n", cmds->envp[i]);
        i++;
    }
}
