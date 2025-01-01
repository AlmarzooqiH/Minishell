// Implement the `unset` built-in command for a custom shell.
// Requirements:
// 1. The `unset` command should remove an environment variable by name.
// 2. The function should take two arguments:
//    - `args`: A null-terminated array of strings where args[1] contains the variable name.
//    - `state`: A shell state structure that contains the environment list (e.g., `state->envp`).
// 3. If the variable does not exist, the command should silently succeed.
// 4. Ensure Norminette compliance:
//    - No function exceeds 25 lines.
//    - Avoid `for` loops and global variables.
// 5. Update the shell's `exit_status` to:
//    - 0 on success.
//    - 1 if no variable name is provided or if there are errors.

#include "includes/minishell.h"

void	builtin_unset(t_commands *cmds)
{
    int i = 1;
    while (cmds->c[cmds->cc][i])
    {
        int j = 0;
        while (cmds->envp[j])
        {
            if (ft_strncmp(cmds->c[cmds->cc][i], cmds->envp[j], ft_strlen(cmds->c[cmds->cc][i])) == 0)
            {
                free(cmds->envp[j]);
                while (cmds->envp[j])
                {
                    cmds->envp[j] = cmds->envp[j + 1];
                    j++;
                }
                break ;
            }
            j++;
        }
        i++;
    }
    cmds->es = 0;
}
