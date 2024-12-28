#include "minishell.h"

// Helper: Check if a string is numeric
static int is_numeric(const char *str)
{
    int i = 0;

    if (!str)
        return (0);
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Main exit function
void builtin_exit(char **args, t_minishell_state *state)
{
    printf("exit\n");
    if (args[1] && !is_numeric(args[1]))
    {
        printf("exit: %s: numeric argument required\n", args[1]);
        cleanup_state(state); // Custom function to free resources
        exit(255);
    }
    if (args[1] && args[2])
    {
        printf("exit: too many arguments\n");
        state->exit_status = 1;
        return;
    }
    cleanup_state(state); // Free memory and other resources
    if (args[1])
        exit(ft_atoi(args[1]));
    exit(state->exit_status);
}
