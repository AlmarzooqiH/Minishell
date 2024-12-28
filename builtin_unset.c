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

void	builtin_unset(char **args, t_minishell_state *state)
{
    if (!args[1])
    {
        state->exit_status = 1;
        return ;
    }
    int i = 0;
    while (state->envp[i])
    {
        if (ft_strncmp(args[1], state->envp[i], ft_strlen(args[1])) == 0)
        {
            free(state->envp[i]);
            while (state->envp[i])
            {
                state->envp[i] = state->envp[i + 1];
                i++;
            }
            state->exit_status = 0;
            return ;
        }
        i++;
    }
    state->exit_status = 0;
}
